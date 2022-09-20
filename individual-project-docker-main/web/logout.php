<?php
session_start();
unset($_SESSION["employee"]);
header("Location:index.php")
?>