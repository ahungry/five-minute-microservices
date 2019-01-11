;; Some REPL based includes.
(use-modules (system repl server))
(use-modules (ice-9 threads))
(use-modules (ice-9 futures))
(use-modules (ice-9 eval-string))
(use-modules (ice-9 regex))
(use-modules ((web server)
              #:select (run-server)
              #:prefix http:))

(catch #t
  (lambda ()
    (spawn-server (make-tcp-server-socket #:port 37146)))
  (lambda (key . parameters)
    #nil))

(define (handler request request-body)
  (values '((content-type . (text/plain)))
          "\"0.0.1\""))

;; ; The defaults: localhost:8080
(http:run-server handler)

;; ; Same thing
;; (run-server handler 'http '())

;; ;; ; On a different port
;; (run-server handler 'http '(#:port 8081))

;; ;; ; IPv6
;; (run-server handler 'http '(#:family AF_INET6 #:port 8081))

;; ;; ; Custom socket
;; (run-server handler 'http `(#:socket ,(sudo-make-me-a-socket)))
