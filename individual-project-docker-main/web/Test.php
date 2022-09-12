<?php   
    $hostName = "mariadb";
    $userName = "root";
    $password = "7YKyE8R2AhKzswfN";
    $dbName = "IoT";
    $conn = new mysqli($hostName,$userName,$password,$dbName);
?>

<!DOCTYPE html>
<html>
<body>
    <h1>Add new user</h1>
    <form action="insert.php" method="POST">
        Username: <input type="text" name="username"><br>
        Forename: <input type="text" name="forename"><br>
        Surname: <input type="text" name="surname"><br>
        Password: <input type="password" name="password"><br>
    <input type="submit">
    </form>
    <br>
</body>
</html>


<?php
    $sql = "SELECT * FROM User";
    $result = $conn->query($sql);

    while($row = $result->fetch_assoc()){
        echo "Username: " . $row["Username"] . "<br>"; 
        echo "Name: " . $row["Forename"] . "<br>";
        echo "Surname: " . $row["Surname"] . "<br><br>";
    }

    $conn->close();
?>