<template>
  <div 
    v-if="showModal"
    class="modal-overlay" 
  >
    <div class="product-options-modal">
      <div class="modal-header">
        <h2>
          {{ product.name }}
        </h2>
        <button @click="closeModal">
          ×
        </button>
      </div>  
      <div 
        v-if="product.name === 'Coffee' || product.name === 'Cappuccino'" 
        class="option"
      >
        <img 
          src="../images/sugar.jpg" 
          alt="Sugar" 
        />
        <div class="option-buttons">
          <button 
            :class="{ selected: selectedSugar === 1 }"
            @click="selectedSugar = 1" 
          >
            1
          </button>
          <div class="separator"></div>
          <button 
            :class="{ selected: selectedSugar === 2 }"
            @click="selectedSugar = 2" 
          >
            2
          </button>
          <div class="separator"></div>
          <button 
            :class="{ selected: selectedSugar === 3 }"
            @click="selectedSugar = 3" 
          >
            3
          </button>
        </div>
      </div>
      <div 
        v-if="product.name === 'Coffee' || product.name === 'Cappuccino'"
        class="option" 
      >
        <img 
          src="../images/coffee-beans.png" 
          alt="Coffee Beans" 
        />
        <div class="option-buttons">
          <button 
            :class="{ selected: selectedStrength === 1 }"
            @click="selectedStrength = 1" 
          >
            1
          </button>
          <div class="separator"></div>
          <button 
            :class="{ selected: selectedStrength === 2 }"
            @click="selectedStrength = 2" 
          >
            2
          </button>
          <div class="separator"></div>
          <button 
            :class="{ selected: selectedStrength === 3 }"
            @click="selectedStrength = 3" 
          >
            3
          </button>
        </div>
      </div>
      <div 
        v-if="product.name === 'Tea'" 
        class="option"
      >
        <select 
          v-model="selectedTeaType" 
          class="tea-type-dropdown"
        >
          <option value="Green Tea">
            Green Tea
          </option>
          <option value="Black Tea">
            Black Tea
          </option>
          <option value="Herbal Tea">
            Herbal Tea
          </option>
        </select>
      </div>
      <div 
        v-if="product.name === 'Chocolate Milk'"
        class="option" 
      >
      </div>
      <map-selection @roomnr="selectRoom"></map-selection>
      <button @click="order">
        Confirm
      </button>
    </div>
  </div>
</template>
  
<script>
import MapSelection from './MapSelection.vue';

export default {
  props: {
    showModal: Boolean,
    product: Object,
  },
  components: {
    MapSelection,
  },
  data() {
    return {
      selectedSugar: 2,
      selectedStrength: 2,
      selectedTeaType: 'Green Tea', // Default tea type
      selectedRoom: 'unknown',
      selectedDrink: this.product.name
    };
  },
  methods: {
    closeModal() {
      this.$emit("close-modal"); // Emit an event to the parent to close the modal
    },
    order() {
      // Pass selected options to the parent component
      // Define a variable to hold the data to be emitted
      const orderData = {
        drink: this.product.name,
        deliver: this.selectedRoom,
      };

      if (this.product.name === 'Coffee' || this.product.name === 'Cappuccino') {
        // Add coffee-specific data
        orderData.sugar = this.selectedSugar;
        orderData.strength = this.selectedStrength;
      } 
      else if (this.product.name === 'Tea') {
        // Add tea-specific data
        orderData.teaType = this.selectedTeaType;
      }

      // Emit the data
      this.$emit("order", orderData);
    },
    selectRoom(room) {
      // Handle room selection logic here, you can use this method to update the selected room in your existing component
      // alert('ordered ' + JSON.stringify(room));
      this.selectedRoom = room;
    },
  },
};
</script>
  
<style scoped>
.modal-overlay {
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

.product-options-modal {
  background-color: white;
  padding: 20px;
  border-radius: 10px;
  box-shadow: 0 0 10px rgba(0, 0, 0, 0.2);
}

.modal-header {
  display: flex;
  align-items: center;
  justify-content: space-between;
}

.close-button {
  font-size: 20px;
  cursor: pointer;
}

.option {
  display: flex;
  align-items: center;
  margin: 10px 0;
}

img {
  width: 40px;
  height: 40px;
}

.option-buttons {
  display: flex;
  gap: 10px;
}

.separator {
  width: 1px;
  background-color: #ccc;
}

button {
  background: #ccc;
  border: none;
  border-radius: 5px;
  padding: 5px 10px;
  cursor: pointer;
}

.selected {
  background: #007BFF;
  color: white;
}

.tea-type-dropdown {
  width: 100%; /* Adjust the width as needed */
}
</style>