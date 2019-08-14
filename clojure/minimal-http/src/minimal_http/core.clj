(ns minimal-http.core
  (:require
   ;; [compojure.route :only [files not-found] :as cr]
   [cheshire.core :as cheshire]
   [compojure.core :only [defroutes GET POST DELETE ANY context] :as cc]
   [org.httpkit.server :as server])
  (:gen-class))

(defn app [req]
  {:status  200
   :headers {"Content-Type" "text/html"}
   :body    "hello HTTP!"})

(defn hello-world [req] {:headers {"content-type" "application/json"} :body "Hello World"})
(defn version [req] {:body "0.0.1"})

(cc/defroutes all-routes
  (cc/GET "/" [] hello-world)
  (cc/GET "/version" [] version))

(defn wrap-headers [handler]
  (fn [req]
    (let [res (handler req)]
      (-> res
          (assoc-in [:headers "content-type"] "application/json")
          ))))

(defn wrap-json [handler]
  (fn [req]
    (let [res (handler req)]
      (-> res
          (update-in [:body] cheshire/generate-string)))))

(def app
  (cc/routes
   (-> all-routes
       (cc/wrap-routes #'wrap-headers)
       (cc/wrap-routes #'wrap-json))))

(defonce server (atom nil))

(defn stop []
  (when-not (nil? @server)
    ;; graceful shutdown: wait 100ms for existing requests to be finished
    ;; :timeout is optional, when no timeout, stop immediately
    (@server :timeout 100)
    (reset! server nil)))

(defn start []
  ;; The #' is useful when you want to hot-reload code
  ;; You may want to take a look: https://github.com/clojure/tools.namespace
  ;; and http://http-kit.org/migration.html#reload
  (reset! server (server/run-server #'app {:port 3000})))

(defn -main [& args]
  (prn "Begin")
  (start))
