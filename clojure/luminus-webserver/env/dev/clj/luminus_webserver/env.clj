(ns luminus-webserver.env
  (:require [selmer.parser :as parser]
            [clojure.tools.logging :as log]
            [luminus-webserver.dev-middleware :refer [wrap-dev]]))

(def defaults
  {:init
   (fn []
     (parser/cache-off!)
     (log/info "\n-=[luminus-webserver started successfully using the development profile]=-"))
   :stop
   (fn []
     (log/info "\n-=[luminus-webserver has shut down successfully]=-"))
   :middleware wrap-dev})
