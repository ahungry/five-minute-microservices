(in-package :cl-user)

(defpackage :5m-ms
  (:use :cl)
  (:export
   :main))

(in-package :5m-ms)

(defun main ()
  (defvar *handler*
    (clack:clackup
     (lambda (env)
       (declare (ignore env))
       '(200 (:content-type "text/plain") ("\"0.0.1\"")))
     :port 12000)))
