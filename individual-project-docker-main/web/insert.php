<?php
    $url = "Test.php";

    $hostName = "mariadb";
    $userName = "root";
    $password = "7YKyE8R2AhKzswfN";
    $dbName = "IoT";
    $conn = new mysqli($hostName,$userName,$password,$dbName);

    $username =  $_REQUEST['username'];
    $forename = $_REQUEST['forename'];
    $surname =  $_REQUEST['surname'];
    $password = $_REQUEST['password'];
         
    // Performing insert query execution
    // here our table name is college
    $sql = "INSERT INTO User VALUES ('$username',
        '$forename','$surname','$password')";
        
    if (mysqli_query($conn, $sql)) {
            echo '<script>alert("User had been added!")</script>';
        } else {
            echo "Error: " . $sql . "<br>" . mysqli_error($conn);
        }
        
    // Close connection
    mysqli_close($conn);
?>