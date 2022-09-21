<?php
    /**
    *   @author     Job van der Knaap
    *   @copyright  Job(2022)
    *   @version    V1.0
    *   Goal: the goal of this code is for an admin to login to the admin website.
    */
    session_start(); // Starts session.
    require "config.php"; // Config file for database connection.

    if (isset($_POST['email']) and isset($_POST['password'])){ // Checks if email and password has been filled in.
        
        // Inserts values into variable.
        $email = $_POST['email'];
        $password = $_POST['password'];

        // adds variable to query.
        $query = "SELECT `name`, `surname`, `email` FROM Employee WHERE email='$email' AND password='$password'";
         
        // Gets result from database and puts in the variable
        $result = mysqli_query($conn, $query) or die(mysqli_error($conn));
        $results = mysqli_fetch_assoc($result); // Full array of data
        $count = mysqli_num_rows($result); // Counts the amount of arrays retrieved

        // Checks if there is one result then proceeds to insert data into the session, otherwise display error.
        if ($count == 1){
            $_SESSION['employee'] = $results;
        }else{
            echo '<script>alert("Wrong credentials, try again.")</script>';
        }
    }

    // If the session is active go to admin page.
    if (isset($_SESSION['employee'])){
        header("Location: tracker.php");
    }
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="/static/css/index.css">
    <title>Log in</title>
</head>
<header>

</header>
<body>
<div class="login-page">
    <div class="form">
        <form class="login-form" method="POST">
            <p>Admin login</p>
            <input type="email" name="email" placeholder="email" required/>
            <input type="password" name="password" placeholder="password" required/>
            <input type="submit" value="login">
        </form>
    </div>
</div>
</body>
<footer>

</footer>
</html>