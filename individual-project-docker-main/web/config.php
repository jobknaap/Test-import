<?php
session_start();
$host = "mariadb"; /* Host name */$user = "root"; /* User */$password = "7YKyE8R2AhKzswfN"; /* Password */$dbname = "IoT"; /* Database name */
$con = mysqli_connect($host, $user, $password,$dbname);
// Check connection
if (!$con) {
  die("Connection failed: " . mysqli_connect_error());
}
