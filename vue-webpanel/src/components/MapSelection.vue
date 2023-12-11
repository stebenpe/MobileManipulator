<template>
    <div class="map-selection">
      <button class="button" @click="showMapSelection">
        Select on Map
      </button>
      <div class="selected-room">
        {{ selectedRoomText }}
      </div>
      <div class="map-overlay" v-if="showMap">
        <button class="close-button" @click="closeMap">&times;</button>
        <div id="image_map" class="map-container">
          <map name="map_example">
            <area href="#" @click="selectRoom('PLC')" alt="PLC" shape="rect" :coords="getCoords('PLC')">
            <area href="#" @click="selectRoom('docenten')" alt="docenten" shape="rect" :coords="getCoords('docenten')">
            <area href="#" @click="selectRoom('studie landschap')" alt="studie landschap" shape="rect" :coords="getCoords('studie_landschap')">
            <area href="#" @click="selectRoom('elektro hoek')" alt="elektro hoek" shape="rect" :coords="getCoords('elektro_hoek')">
          </map>
          <img
            src="../images/G2.png"
            alt="image map example"
            :width="isMobile ? 473 : 1300"
            :height="isMobile ? 182 : 500"
            usemap="#map_example"
          />
        </div>
      </div>
    </div>
  </template>
  
  <script>
  export default {
    data() {
      return {
        showMap: false, // Flag to control map display
        selectedRoom: null, // Store the selected room
        isMobile: false, // Flag to check if it's a mobile screen
      };
    },
  
    computed: {
      selectedRoomText() {
        return this.selectedRoom ? `Selected Room: ${this.selectedRoom}` : 'Nothing selected';
      },
    },
  
    methods: {
      showMapSelection() {
        this.showMap = true; // Show the map overlay
      },
      closeMap() {
        this.showMap = false; // Close the map overlay
      },
      selectRoom(room) {
        this.selectedRoom = room;
        this.$emit('roomnr',room);
        this.showMap = false; // Close the map overlay
      },
      getCoords(room) {
        const coordinates = {
          PLC: [34,200,250,350],
          docenten: [500,150, 630,250],
          studie_landschap: [400,300, 750,400],
          elektro_hoek: [1050,150,1175,250],
        };
        return coordinates[room].map((coord) => (this.isMobile ? coord / 2.75: coord)).join(',');
      },
    },
  
    mounted() {
      // Check if it's a mobile screen (you can adjust the width threshold)
      this.isMobile = window.innerWidth <= 768;
  
      // Add an event listener to update isMobile on window resize
      window.addEventListener('resize', () => {
        this.isMobile = window.innerWidth <= 768;
      });
    },
  };
  </script>
  
  <style scoped>
  /* Add your map and room selection styles here */
  .map-overlay {
    position: fixed;
    top: 0;
    left: 0;
    width: 100%;
    height: 100%;
    background-color: rgba(0, 0, 0, 0.7);
    display: flex;
    align-items: center;
    justify-content: center;
    z-index: 999;
  }
  
  .close-button {
    font-size: 20px;
    color: white;
    cursor: pointer;
    background: transparent;
    border: none;
    position: absolute;
    top: 10px;
    right: 10px;
    z-index: 1000;
  }
  
  .map-container {
    position: relative;
  }
  
  .responsive-image {
    width: 1300px;
    height: 500px;
  }
  
  button {
    background: #ccc;
    border: none;
    border-radius: 5px;
    padding: 5px 10px;
    cursor: pointer;
  }
  </style>
  