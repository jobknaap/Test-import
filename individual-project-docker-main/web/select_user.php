<?php
    require "config.php";
    $userId;
    $statusCheck;
    $insertStatus;

    $checkOut = 0;
    $checkIn = 1;

    $rfid = $_REQUEST['rfid'];
    
    $query = "SELECT Employee.employee_id, CheckIn.checked_in FROM Employee INNER JOIN CheckIn ON Employee.employee_id = CheckIn.employee_id WHERE Employee.rfid='" . $rfid . "' ORDER BY CheckIn.date_time DESC LIMIT 1";
    $result = $conn->query($query);
    
    while ($row= $result->fetch_assoc()) {
        $employeeId = intval($row['employee_id']);
        $statusCheck = intval($row['checked_in']);
    }

    if ($statusCheck == $checkOut){
        $insertStatus = $conn->prepare("INSERT INTO `CheckIn` (checked_in, date_time, employee_id) VALUES (?, NOW(), ?)");
        $insertStatus->bind_param('ii', $checkIn, $employeeId);
    } else {
        $insertStatus = $conn->prepare("INSERT INTO `CheckIn` (checked_in, date_time, employee_id) VALUES (?, NOW(), ?)");
        $insertStatus->bind_param('ii', $checkOut, $employeeId);
    }

    $insertStatus->execute();
      
    $conn->close();

?>