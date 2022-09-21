<?php
    session_start();
    require "config.php";

    if (isset($_POST['email']) and isset($_POST['password'])){
        $email = $_POST['email'];
        $password = $_POST['password'];
        $query = "SELECT * FROM `employee` WHERE email='$email' AND password='$password'";
         
        $result = mysqli_query($conn, $query) or die(mysqli_error($conn));
        $results = mysqli_fetch_assoc($result);
        $count = mysqli_num_rows($result);
        if ($count == 1){
            $_SESSION['employee'] = $results;
        }else{
            echo '<script>alert("Wrong credentials, try again.")</script>';
        }
    }

    if (isset($_SESSION['employee'])){
        header("Location: admin.php");
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
            <input type="email" name="email" placeholder="email"/>
            <input type="password" name="password" placeholder="password"/>
            <input type="submit" value="login">
        </form>
    </div>
</div>
</body>
<footer>

</footer>
</html>