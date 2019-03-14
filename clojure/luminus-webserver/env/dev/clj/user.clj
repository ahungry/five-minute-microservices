(ns user
  (:require [luminus-webserver.config :refer [env]]
            [clojure.spec.alpha :as s]
            [expound.alpha :as expound]
            [mount.core :as mount]
            [luminus-webserver.core :refer [start-app]]))

(alter-var-root #'s/*explain-out* (constantly expound/printer))

(defn start []
  (mount/start-without #'luminus-webserver.core/repl-server))

(defn stop []
  (mount/stop-except #'luminus-webserver.core/repl-server))

(defn restart []
  (stop)
  (start))


