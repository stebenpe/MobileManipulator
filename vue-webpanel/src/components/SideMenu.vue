<template>
    <div class="side-menu" :class="{ 'menu-visible': isVisible }">
      <router-link to="/">Home</router-link>
      <router-link to="/about">About</router-link>
      <router-link to="/order">Order</router-link>
      <button @click="logout">Logout</button>
    </div>
</template>
  
<script>
  export default {
    props: {
      isVisible: Boolean, // Prop to control the visibility of the side menu
    },
    methods: {
      logout() {
        this.$emit("logout"); // Emit the logout event to the parent component
      },
    },
  };
</script>
  
<style scoped>
  .side-menu {
    position: fixed;
    top: 0;
    left: 0; /* Initially, the side menu is visible */
    width: 250px;
    height: 100%;
    background-color: #333;
    color: #fff;
    display: flex;
    flex-direction: column;
    align-items: center;
    justify-content: center;
    z-index: 1000;
    transition: left 0.3s; /* Add a smooth slide-in animation */
  }
  
  .menu-visible {
    left: -250px; /* Move the side menu out of the viewport initially */
  }
  
  .side-menu button {
    margin-top: 20px;
  }
</style>
  