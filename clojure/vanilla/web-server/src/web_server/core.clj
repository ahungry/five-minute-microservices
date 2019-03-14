;; A starting point at least... https://github.com/atroche/clj-sockets/blob/master/src/clj_sockets/core.clj
;; Needs a lot of work - the wrapper doesn't handle more than one server response at a time etc.
(ns web-server.core
  (:require
   [clj-sockets.core :refer [listen create-socket write-to close-socket
                             create-server
                             read-line read-lines write-line]]))



(defn -main [& args]
  (println "Running on port 9873")
  (while true
    (def server (listen (create-server 9873)))
    (read-line server)
    (write-line server "Hi")
    ;; (close-socket server)
    )
  )

(defn foo
  "I don't do a whole lot."
  [x]
  (println x "Hello, World!"))
