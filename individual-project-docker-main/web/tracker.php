<?php
    /**
    *   @author     Job van der Knaap
    *   @copyright  Job(2022)
    *   @version    V1.0
    *   Goal: the goal of this code is for an admin to track the employees to see if they are inside the building and track when the last person checked in or out.
    *
    */
    session_start(); // Resumes session of admin.
    require "config.php"; // Database connection.

    // Checks if session is active if not return to login screen for security.
    if(!isset($_SESSION['employee'])){
        header("Location: index.php");
    }

    // Query to get the correct data from the employees and insert data into to variable.
    $status = "SELECT Employee.name, Employee.surname, CheckIn.checked_in FROM Employee INNER JOIN CheckIn ON Employee.employee_id = CheckIn.employee_id";
    $statusResult = $conn->query($status);

    $tracker = "SELECT Employee.name, Employee.surname, CheckIn.checked_in, CheckIn.date_time FROM Employee INNER JOIN CheckIn ON Employee.employee_id = CheckIn.employee_id ORDER BY date_time DESC LIMIT 10";
    $trackerResult = $conn->query($tracker);
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="/static/css/app.css">
    <link rel="stylesheet" href="/static/css/tracker.css">
    <title>Tracker</title>
</head>
<header>
    <nav>
        <ul>
            <li>Time management -
                <?php
                    echo $_SESSION['employee']['name'] . " " . $_SESSION['employee']['surname']; // Display the user who is active in the session
                ?>
            </li>
            <li class="navbar-items"><a href="logout.php">Log out</a></li>
            <li class="navbar-items"><a href="admin.php">Administration</a></li>
            <li class="navbar-items"><a href="tracker.php" class="active">Tracker</a></li>
        </ul>
    </nav>
</header>
<body>
    <div class="tracker-container">
        <div class="in-office-container">
            <h1>In the office</h1>
            <table>
                <thead>
                    <th>Status</th>
                    <th>Employee</th>
                </thead>
                <tbody>
                    <?php
                        // For loop to show the data in the table.
                        foreach($statusResult as $row => $value):
                    ?>
                        <tr>
                            <td>
                                <?php 
                                    // If the employee isn't "checked-in"(0) then display red otherwise display green.
                                    if($value['checked_in'] == 0){
                                        echo '<img src="/static/images/inactive.png" alt="Small red orb to display checked-out personnel.">';
                                    }else{
                                        echo '<img src="/static/images/active.png" alt="Small green orb to display checked-out personnel.">';
                                    }
                                ?>
                            </td>
                            <td>
                                <?=
                                    // Displays employees full names.
                                    $value['name'] . " " . $value['surname'];
                                ?>
                            </td>
                        </tr>
                    <?php endforeach; ?>
                </tbody>
            </table>
        </div>
        <div class="check-in-container">
            <h1>Last check-in & - outs</h1>
            <table>
                <thead>
                    <th>Employee</th>
                    <th>Date</th>
                    <th>Time</th>
                    <th>Status</th>
                </thead>
                <tbody>
                    <?php
                        // For loop to show the data in the table.
                        foreach($trackerResult as $row => $value):
                    ?>
                    <tr>
                        <td>
                            <?=
                                // Display employees full name. 
                                $value['name'] . " " . $value['surname']
                            ?>
                        </td>
                        <td>
                            <?= date('Y-m-d', strtotime($value['date_time']))?>
                        </td>
                        <td>
                            <?= date('H:i', strtotime($value['date_time']))?>
                        </td>
                        <td>
                            <?php 
                                // If the employee isn't "checked-in"(0) then display red otherwise display green.
                                if($value['checked_in'] == 0){
                                    echo 'Checked out';
                                }else{
                                    echo 'Checked in';
                                }
                            ?>
                        </td>
                    </tr>
                    <?php endforeach; ?>
                </tbody>
            </table>
        </div>
    </div>
</body>
<footer>

</footer>
</html>

