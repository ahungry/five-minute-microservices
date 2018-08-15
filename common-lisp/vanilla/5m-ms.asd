(in-package :cl-user)

(defpackage 5m-ms-asd
  (:use :cl :asdf))

(asdf:defsystem :5m-ms
    :version "0.0.1"
    :description "Five minute microservice"
    :license "AGPLv3"
    :author "Matthew Carter <m@ahungry.com>"
    :depends-on (:clack)
    :serial t
    :components
    ((:module "5m-ms"
              :pathname "src"
              :components
              ((:file "5m-ms")))))
