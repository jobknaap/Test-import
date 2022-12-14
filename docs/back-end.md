# Back-end

### Index.php
My index page is an login page, because the user is an admin. [Link to full file](https://gitlab.fdmci.hva.nl/IoT/2022-2023-sep-jan/individual-project/iot-knaapj/-/blob/main/individual-project-docker-main/web/index.php)<br>
``` PHP
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
```

---

### Tracker.php
The traker page is to see which employee is in or outside the building and also to see the latest check-ins or -outs. [Link to full file](https://gitlab.fdmci.hva.nl/IoT/2022-2023-sep-jan/individual-project/iot-knaapj/-/blob/main/individual-project-docker-main/web/tracker.php)<br><br>
This part is for retreiving the data and putting it in a variable.
``` PHP
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
```

??? Table_status
    This part is to display the status of the people who are in or outside. the building.
    ``` PHP
        <table>
            <thead>
                <th>Status</th>
                <th>Employee</th>
            </thead>
            <tbody>
                <?php
                    // For loop to show the data in the table.
                    foreach($result as $row => $value):
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
                <?php endforeach;?>
            </tbody>
        </table>
    ```

??? Table_tracker
    This part is to display the last check in and outs.
    ``` PHP
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
    ```

---

### Logout.php
Small line of code that logs out the admin. [Link to file](https://gitlab.fdmci.hva.nl/IoT/2022-2023-sep-jan/individual-project/iot-knaapj/-/blob/main/individual-project-docker-main/web/logout.php)<br>

``` PHP
<?php
    session_start(); // Resumes session

    // Removes current session and redirects to the login screen.
    unset($_SESSION["employee"]); 
    header("Location:index.php")
?>
```