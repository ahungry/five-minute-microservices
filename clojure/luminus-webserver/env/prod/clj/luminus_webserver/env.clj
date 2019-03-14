(ns luminus-webserver.env
  (:require [clojure.tools.logging :as log]))

(def defaults
  {:init
   (fn []
     (log/info "\n-=[luminus-webserver started successfully]=-"))
   :stop
   (fn []
     (log/info "\n-=[luminus-webserver has shut down successfully]=-"))
   :middleware identity})
