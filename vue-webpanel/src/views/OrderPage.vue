<template>
  <div>
    <product 
      :name="'Coffee'"
      :calories="120"
      :image="'coffee.jpg'"
      @handleOrderParent="handleOrder"
    >
    </product>
    <product 
      :name="'Tea'"
      :calories="0"
      :image="'tea.png'"
      @handleOrderParent="handleOrder"
    >
    </product>
    <product 
      :name="'Cappuccino'"
      :calories="150" 
      :image="'cappuccino.jpg'"
      @handleOrderParent="handleOrder"
    >
    </product>
    <product 
      :name="'Chocolate Milk'" 
      :calories="200" 
      :image="'chocolate-milk.jpg'"
      @handleOrderParent="handleOrder"
    >
    </product>
  </div>
</template>
  
<script>
import Product from '../components/OrderProduct.vue'; // Import the product component
import * as ROSLIB from 'roslib'

export default {
  data() {
    return {
      options: {},
      orderMessage: null,
    };
  },

  components: {
    product: Product, // Register the product component
  },

  methods: {
    handleOrder(options) {
      // Handle the order with selected options (options.sugar and options.strength)
      alert('ordered ' + JSON.stringify(options));
      // Convert the fields to the appropriate data types
      const data = {
        drink: options.drink,
        deliver: options.deliver,
      };

      if (options.drink === 'Coffee' || options.drink === 'Cappuccino') {
        // Convert sugar and strength to integers
        data.sugar = parseInt(options.sugar, 10);
        data.strength = parseInt(options.strength, 10);
      } else if (options.drink === 'Tea') {
         // Leave tea_type as a string
         data.tea_type = options.teaType;
      }

      this.orderMessage = data;

      // publisch to ros2 topic
      const Order = new ROSLIB.Topic({
        ros : this.ros,
        name : '/Order',
        messageType : 'topics_services/msg/Order'
      });

      const msg = new ROSLIB.Message(this.orderMessage);

      Order.publish(msg);
    },
  },

  mounted() {
    //conect to ros2 socket
    this.ros = new ROSLIB.Ros({
      url: "ws://localhost:9090"
    });

    this.ros.on('connection', () => {
      console.log('Connected to Rosbridge server');
    });

    this.ros.on('error', (error) => {
      console.error('Error connecting to Rosbridge server:', error);
    });

    this.ros.on('close', () => {
      console.log('Connection to Rosbridge server closed');
    });

    this.ros.connect(); // Connect to Rosbridge server    
  }
};
</script>