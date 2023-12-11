<template>
  <div class="container">
    <div 
      id="app"
      class="m-0 p-0 row"
    >
      <div class="card text-center col-12 mt-1 w-100">
        <RecognitionSensorDisplay>
        </RecognitionSensorDisplay>
      </div>
      <div>
        <ProgressBar 
          :ordernr="this.retrievedData.order_nr" 
          :state="this.retrievedData.delivery_state" 
          :drink="this.retrievedData.drink" 
          :eta_min="this.retrievedData.eta_min"
          :eta_sec="this.retrievedData.eta_sec"
        >
        </ProgressBar>
      </div>
      <div class="col-md-6">
        <div class="responsive-container">
          <iframe 
            src="https://ia.elektrotechniek.nhlstenden.com/" 
            width="100%" 
            height="400"
          >
          </iframe>
        </div>
      </div>
      <div class="col-md-6">
        <div class="responsive-container">
          <div class="VideoComponent">
            <VideoComponent />
          </div>
        </div>
      </div>
    </div>
    <div class="card col-12 mt-1 w-100">
      <TestBridgeComponent />
    </div>
  </div>
</template>
  
<script>
  // import LineChartComponent from './components/LineChartComponent.vue';
  // import config from '../config.js';
  import * as ROSLIB from 'roslib';
  import RecognitionSensorDisplay from '../components/RecognitionSensorDisplay.vue';
  import TestBridgeComponent from '../components/TestBridgeComponent.vue';
  import VideoComponent from '../components/VideoComponent.vue';
  import Progress from '../components/ProgressBar.vue'; // Import the product component
  
  export default {
      name: 'HomePage',
      components: {
      RecognitionSensorDisplay,
      TestBridgeComponent,
      VideoComponent,
      ProgressBar: Progress,
  },
    data() {
      return {
        retrievedData: {},
      };
    },
    created() {
      try {
        const ros = new ROSLIB.Ros({
          url: "ws://localhost:9090"
        });
  
        const listener = new ROSLIB.Topic({
          ros,
          name: '/Telemetric',
          messageType: 'topics_services/msg/Telemetric',
        });
  
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