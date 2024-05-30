<?php
ini_set('display_errors', 1); // set to 0 for production version
ini_set('display_startup_errors', 1);
error_reporting(E_ALL); // Report all PHP errors
?>

 <?php

$db_servername = "localhost";
$db_username = "root";
$db_password = "root";
$db_name = "GPSDatabase";

// Create connection
$conn = new mysqli($db_servername ,$db_username, $db_password, $db_name);

// Check connection
if ($conn->connect_error) {
  die("Connection failed: " . $conn->connect_error);
}

// prepare sql query
$sql = "SELECT id, value, measurement_date FROM GPS ORDER BY id DESC LIMIT 15";
$result_data_GPS = $conn->query($sql);

// prepare sql query
$sql = "SELECT id, file_name, creation_date FROM photo ORDER BY id DESC LIMIT 15";
$result_data_photos = $conn->query($sql);

// close database connection
$conn->close();

?>
<!DOCTYPE html>

<html>
<head>
    <title>Gruppe 2 Drone projekt - Arduino,Raspberry,GPS og billede</title>
    <meta http-equiv="refresh" content="60"> <!-- refresh page automatically refresh a web page in 60 seconds -->
</head>
<style>
table, th, td {
  border:1px solid grey;
  padding: 5px;
}

th {
        background: #c9cdd4;
}
div {
  float: left;
  padding: 15px;
}

.div1 {
  background: #e6e8eb;
}

.div2 {
  background: #ccd9ed;
}

</style>

<body>

<h2>Gruppe 2 Data: Raspberry Pi, Camera, Arduino, GPS location</h2>
<a href="http://152.115.77.165:50308" <button style="font-size: 20px; background-color: pink;"> Tilbage til frontpage </button> </a>
<p>Her er vores HTML sidde som viser dataen fra vores MySQL server. <br> Grunden til at id nr 2,3 og 5 er tomme er pga af sleep funktionen i raspberry, hvilket gjorde at den ikke altid fik GPS, dette er en fejl som løses ved at fjerne den lille sleep funktion <br> Vi valgte dog at beholde sleep her for at undgå spam af billeder.</p>


<div class="div1">

<table style="">
  <tr>
    <th colspan="3" scope="colgroup">Photos</th>
  </tr>
  <tr>
    <th>Id</th>
        <th>Photo</th>
    <th>Date and time</th>
  </tr>

  <?php

  $img_target_dir = "data-rpi/images/";
  foreach ($result_data_photos as $row)
  {
          echo "<tr>";
          echo "<td>".$row["id"]."</td>";/**/
          echo '<td><img src="'.$img_target_dir.$row["file_name"].'" alt="" width="640" height="480"></td>';
          echo "<td>".$row["creation_date"]."</td>";
          echo "</tr>";
  }

        ?>

</table>

</div>

<div class="div2">
<table style="">
  <tr>
    <th colspan="3" scope="colgroup">GPS</th>
  </tr>
  <tr>
    <th>Id</th>
        <th>Value</th>
    <th>Date and time</th>
  </tr>

  <?php
  foreach ($result_data_GPS as $row)
  {
          echo "<tr>";
          echo "<td>".$row["id"]."</td>";
          echo "<td>".$row["value"]."</td>";
          echo "<td>".$row["measurement_date"]."</td>";
          echo "</tr>";
  }
  ?>


</table>
</div>

</body>
</html>
