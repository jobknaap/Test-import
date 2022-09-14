<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="/static/css/app.css">
    <link rel="stylesheet" href="/static/css/home.css">
    <title>Tracker</title>
</head>
<header>
    <nav>
        <ul>
            <li>Time management</li>
            <li class="navbar-items"><a href="#">Log out</a></li>
            <li class="navbar-items"><a href="data.php">Administration</a></li>
            <li class="navbar-items"><a href="admin.php" class="active">Tracker</a></li>
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
                    <tr>
                        <td><img src="/static/images/inactive.png" alt="Small red orb to display checked-out personnel."></td>
                        <td>Dwight Schrute</td>
                    </tr>
                    <tr>
                        <td><img src="/static/images/active.png" alt="Small green orb to display checked-out personnel."></td>
                        <td>Michael Scott</td>
                    </tr>
                    <tr>
                        <td><img src="/static/images/active.png" alt="Small green orb to display checked-out personnel."></td>
                        <td>Michael Scott</td>
                    </tr>
                    <tr>
                        <td><img src="/static/images/inactive.png" alt="Small red orb to display checked-out personnel."></td>
                        <td>Michael Scott</td>
                    </tr>
                    <tr>
                        <td><img src="/static/images/active.png" alt="Small green orb to display checked-out personnel."></td>
                        <td>Michael Scott</td>
                    </tr>
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
                    <tr>
                        <td>Michael Scott</td>
                        <td>14-09-2022</td>
                        <td>13:33</td>
                        <td>Checked-in</td>
                    </tr>
                </tbody>
            </table>
        </div>
    </div>
</body>
<footer>

</footer>
</html>

