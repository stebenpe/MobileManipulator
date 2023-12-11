<template>
  <div class="about">
    <h1 id="mobilemanipulator">
      MobileManipulator
    </h1>
    <p>
      Ik ben Steven Pennock en ik heb als stage opdracht gekregen om koffie te halen.
      Nou heb ik natuurlijk helemaal geen zin om zelf iedere keer koffie te halen dus daarom ga ik een Mobile Manupulator (MoMa) maken.
    </p>
    <p>
      Hieronder is een overzicht te zien van het programma zoals het nu de gedachte is:
    </p>
    <img 
      class="picture-1"
      src="../images/programma-overzicht.jpg" 
      alt="1"
    >
    <h1 id="inhoudsopgave">
      Inhoudsopgave
    </h1>
    <ul>
      <li>Progressie</li>
      <li>Onderdelen</li>
      <li>Netwerk</li>
      <li>Website</li>
      <li>LD-90</li>
      <li>Omron TM5-900</li>
      <li>ZED 2i</li>
      <li>NVIDIA jetson orin AGX</li>
    </ul>
    <h2 id="progressie">
      Progressie
    </h2>
    <p>
      Componenten:
    </p>
    <ul>
      <li>[x] Uitzoeken 3D camera</li>
      <li>[x] Uitzoeken embedded AI computer</li>
      <li>[x] Uitzoeken robot arm</li>
    </ul>
    <p>
      Netwerk:
    </p>
    <ul>
      <li>[x] Instellen mikrotik als bridge met school wifi en eigen subnet</li>
      <li>[x] Instellen mikrotik met vaste ip&#39;s</li>
      <li>[x] ROS2 netwerk instellingen toepassen</li>
      <li>[ ] VPN connectie naar router netwerk</li>
    </ul>
    <p>
      ROS2:
    </p>
    <ul>
      <li>[x] ROS2 installeren op RPI 4 en laptop</li>
      <li>[x] LD-90 aansturen met ROS2</li>
      <li>[ ] URDF samenvoegen LD-90, 3D camera, robot arm en gripper</li>
      <li>[ ] 3D camera koppelen met ROS2</li>
      <li>[ ] 3D map genereren met 3D camera</li>
      <li>[ ] Ordering systeem koppelen met ROS2</li>
      <li>[ ] MoveIT2 instellen robot arm</li>
    </ul>
    <p>
      Website:
    </p>
    <ul>
      <li>[x] Website maken</li>
      <li>[x] Data LD-90 visualiseren op website</li>
      <li>[ ] RVIZ2 visualiseren op website</li>
      <li>[ ] Ordering systeem maken</li>
      <li>[ ] InfluxDB koppelen</li>
    </ul>
    <h2 id="onderdelen">
      Onderdelen
    </h2>
    <ul>
      <li>Omron LD-90 AMR (met zei lidar)</li>
      <li>Omron TM5-900 robot arm</li>
      <li>Robotiq 2F-85 gripper</li>
      <li>ZED 2i 3D camera</li>
      <li>NVIDIA jetson orin AGX embedded AI computer</li>
      <li>MikroTik router</li>
    </ul>
    <h2 id="netwerk">
      Netwerk
    </h2>
    <p>
      Hieronder is een overzicht te zien van hou het huidige netwerk in elkaar zit:
    </p>
    <img 
      class="picture-2"
      src="../images/netwerk.jpg" 
      alt="2"
    >
    <h2 id="website">
      Website
    </h2>
    <h2 id="ld-90">
      LD-90
    </h2>
    <h2 id="omron-tm5-900">
      Omron TM5-900
    </h2>
    <h2 id="zed-2i">
      ZED 2i
    </h2>
    <h2 id="nvidia-jetson-orin-agx">
      Nvidia jetson orin AGX
    </h2>
    <p>
      [^1]: Gemaakt door Steven Pennock 2023.
    </p>
  </div>
</template>

<style scoped>
.about {
  text-align: left;
}

.picture-1 {
  width: 700px;
  height: 800px;
  object-fit: cover;
}

.picture-2 {
  width: 600px;
  height: 400px;
  object-fit: cover;
}
</style>