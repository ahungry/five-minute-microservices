(ns luminus-webserver.routes.home
  (:require [luminus-webserver.layout :as layout]
            [compojure.core :refer [defroutes GET]]
            [ring.util.http-response :as response]
            [clojure.java.io :as io]))

(defn json-version []
  {:body "0.0.1"})

(defn home-page [request]
  (layout/render request "home.html" {:docs (-> "docs/docs.md" io/resource slurp)}))

(defn about-page [request]
  (layout/render request "about.html"))

(defroutes home-routes
  (GET "/" [] (json-version))
  ;; (GET "/" request (home-page request))
  (GET "/about" request (about-page request)))
