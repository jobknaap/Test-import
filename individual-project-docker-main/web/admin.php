<?php
session_start();
require "config.php";
if(!isset($_SESSION['employee'])){
    header("Location: index.php");
}
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="/static/css/app.css">
    <link rel="stylesheet" href="/static/css/admin.css">
    <title>Administration</title>
</head>
<header>
    <nav>
        <ul>
            <li>Time management - <?php echo $_SESSION['employee']['name'] . " " . $_SESSION['employee']['surname']; ?></li>
            <li class="navbar-items"><a href="logout.php">Log out</a></li>
            <li class="navbar-items"><a href="admin.php" class="active">Administration</a></li>
            <li class="navbar-items"><a href="tracker.php">Tracker</a></li>
        </ul>
    </nav>
</header>
<body>
    <div class="employees-container">
        <h1>Employees</h1>
        <table>
            <thead>
                <th>Name</th>
                <th>Surname</th>
                <th>Phone number</th>
                <th>RFID</th>
            </thead>
            <tbody>
                <tr>
                    <td>Michael</td>
                    <td>Scott</td>
                    <td>0612345678</td>
                    <td>237,131,63,89,8</td>
                    <td>
                        <a href="#"><img src="/static/images/edit.png" alt="Edit icon."></a>
                        <a href="#"><img src="/static/images/delete.png" alt="Delete icon."></a>
                    </td>
                </tr>
                <tr>
                    <td>Michael</td>
                    <td>Scott</td>
                    <td>0612345678</td>
                    <td>237,131,63,89,8</td>
                    <td>
                        <a href="#"><img src="/static/images/edit.png" alt="Edit icon."></a>
                        <a href="#"><img src="/static/images/delete.png" alt="Delete icon."></a>
                    </td>
                </tr>
                <tr>
                    <td>Michael</td>
                    <td>Scott</td>
                    <td>0612345678</td>
                    <td>237,131,63,89,8</td>
                    <td>
                        <a href="#"><img src="/static/images/edit.png" alt="Edit icon."></a>
                        <a href="#"><img src="/static/images/delete.png" alt="Delete icon."></a>
                    </td>
                </tr>
            </tbody>
        </table>
    </div>
</body>
<footer>

</footer>
</html>