<template>
  <div 
    class="product-box"
    :width="isMobile ? 400 : 350"
  >
    <div class="product-image">
      <img
        v-if="name === 'Coffee'"
        src="../images/coffee.jpg"
        alt="Coffee"
        :width="isMobile ? 400 : 350"
        :height="isMobile ? 400 : 350"
      />
      <img 
        v-else-if="name === 'Tea'" 
        src="../images/tea.png" 
        alt="Tea" 
        :width="isMobile ? 400 : 350"
        :height="isMobile ? 400 : 350"
      />
      <img
        v-else-if="name === 'Cappuccino'"
        src="../images/cappuccino.jpg"
        alt="Cappuccino"
        :width="isMobile ? 400 : 350"
        :height="isMobile ? 400 : 350"
      />
      <img
        v-else-if="name === 'Chocolate Milk'"
        src="../images/chocolate-milk.jpg"
        alt="Chocolate Milk"
        :width="isMobile ? 400 : 350"
        :height="isMobile ? 400 : 350"
      />
    </div>
    <h2>{{ name }}</h2>
    <p class="calories">
      Calories: {{ calories }}
    </p>
    <button 
      class="order-button" 
      @click="showModal = true"
    >
      Order
    </button>
    <product-options-modal
      :show-modal="showModal"
      :product="{
        name,
        calories,
        image,
      }"
      @close-modal="closeModalHandler"
      @order="handleOrder"
    ></product-options-modal>
  </div>
</template>

<script>
import ProductOptionsModal from "./ProductOptionsModal.vue";

export default {

  props: {
    name: String,
    calories: Number,
    image: String,
  },

  data() {
    return {
      showModal: false,
      isMobile: false, // Flag to check if it's a mobile screen
    };
  },

  components: {
    ProductOptionsModal,
  },

  methods: {
    closeModalHandler(){
      this.showModal = false;
    },
    handleOrder(options) {
      // Handle the order with selected options (options.sugar and options.strength)
      this.$emit('handleOrderParent', options)
      // Close the modal
      this.showModal = false;
    },
  },
  mounted() {
    // Check if it's a mobile screen (you can adjust the width threshold)
    this.isMobile = window.innerWidth <= 768;
  
    // Add an event listener to update isMobile on window resize
    window.addEventListener('resize', () => {
      this.isMobile = window.innerWidth <= 768;
    });
  }
}
</script>

<style scoped>
.product-box {
  background-color: #f5f5f5;
  border-radius: 20px;
  padding: 20px;
  text-align: center;
  margin: 15px;
  display: inline-block;
  box-shadow: 0 4px 8px rgba(0, 0, 0, 0.1);
}

.product-image {
  overflow: hidden;
  border-radius: 20px;
}

.product-image img {
  object-fit: cover;
}

h2 {
  font-size: 24px;
  color: #333;
  margin-top: 10px;
}

.calories {
  font-size: 16px;
  color: #666;
}

.order-button {
  background-color: #007BFF;
  color: white;
  border: none;
  border-radius: 5px;
  padding: 10px 20px;
  cursor: pointer;
  font-weight: bold;
  margin-top: 10px;
}
</style>
