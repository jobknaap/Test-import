<?php
    session_start(); // Resumes session

    // Removes current session and redirects to the login screen.
    unset($_SESSION["employee"]); 
    header("Location:index.php")
?>