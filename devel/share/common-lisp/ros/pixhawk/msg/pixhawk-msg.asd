
(cl:in-package :asdf)

(defsystem "pixhawk-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :std_msgs-msg
)
  :components ((:file "_package")
    (:file "Num" :depends-on ("_package_Num"))
    (:file "_package_Num" :depends-on ("_package"))
    (:file "imu_gps" :depends-on ("_package_imu_gps"))
    (:file "_package_imu_gps" :depends-on ("_package"))
  ))