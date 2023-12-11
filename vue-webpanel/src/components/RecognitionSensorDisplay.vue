<template>
  <div class="card">
    <h3>Robot stats</h3>
    <div class="align-items-center">
    </div>
    <table class="table custom-table">
      <tr>
        <th 
          scope="row" 
          style="color: black;"
        >
          battery percentage:
        </th>
        <td 
          style="color: black;"
        >
          {{ (this.retrievedData.percentage) }}%
        </td>
      </tr>
      <tr>
        <th 
          scope="row" 
          style="color: black;"
        >
          battery voltage:
        </th>
        <td 
          style="color: black;"
        >
          {{ (this.retrievedData.voltage) }} Volt
        </td>
      </tr>
      <tr>
        <th 
          scope="row" 
          style="color: black;"
        >
          robot coordinates:
        </th>
        <td 
          style="color: black;"
        >
          {{ (this.retrievedData.coordinates_x) }}, {{ (this.retrievedData.coordinates_y) }} X,Y
        </td>
      </tr>
      <tr>
        <th 
          scope="row" 
          style="color: black;"
        >
          power draw:
        </th>
        <td 
          style="color: black;"
        >
          {{ (this.retrievedData.power) }} Watt
        </td>
      </tr>
      <tr>
        <th 
          scope="row" 
          style="color: black;"
        >
          ETA task:
        </th>
        <td 
          style="color: black;"
        >
          {{ (this.retrievedData.eta_min) }}min, {{ (this.retrievedData.eta_sec) }} sec
        </td>
      </tr>
    </table>
  </div>
</template>

<script>
import * as ROSLIB from 'roslib'
// import config from '/src/config.js';

export default {
    name: 'RecognitionSensorDisplay',
    components: {},
         /*using data() for reactive properties within the code. 
    vue will track the changes and update the DOM when data changes
    in this case i do so because i'd like the chart to have its data available on render. otherwise i could have technically used props
    in this case we don't need a prop because the component handles its own requists
    */
    data() {
        return {
            retrievedData: {},
        };
    },
    //set up websocket for dynamic data display
    mounted() {
        try {
            const ros = new ROSLIB.Ros({
              url: "ws://localhost:9090"
            });

            const listener = new ROSLIB.Topic({
                ros,
                name: '/Telemetric',
                messageType: 'topics_services/msg/Telemetric',
            });
            //listener event defenition
            listener.subscribe((message) => {
                this.retrievedData = message;
            });

            ros.on('connection', () => {
                console.log('Connected to Rosbridge server');
            });

            ros.on('error', (error) => {
                console.error('Error connecting to Rosbridge server:', error);
            });

            ros.on('close', () => {
                console.log('Connection to Rosbridge server closed');
            });

            ros.connect(); // Connect to Rosbridge server
        } catch (error) {
            console.error('An error occurred while connecting to Rosbridge server:', error);
        }
    }
}
</script>

<style scoped>
.card {
    z-index: 0;
    background-color: #ECEFF1;
    padding-bottom: 20px;
    margin-top: 15px;
    margin-bottom: 15px;
    border-radius: 10px;
}
.custom-table {
  background-color: white;
  margin-top: 15px;
}

</style>