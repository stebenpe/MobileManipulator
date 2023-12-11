<template>
  <div class="app">
    <div class="top-left">
      <div v-if="isSideMenuVisible">
          test
      </div>
      <div v-if="isMobile">
        <div @click="openMenu" class="hamburger-menu">
          <div class="line"></div>
          <div class="line"></div>
          <div class="line"></div>
        </div>
        <SideMenu v-if="isSideMenuVisible" :is-visible="isSideMenuVisible" @logout="logout" />
      </div>
      <div v-else class="head text">
        <img 
          style="height: 60px; 
          width: 60px; 
          display: inline;" 
          src="images/MoMa_logo.png"
        >
        <h3 
          class="col-5" 
          style="display: inline;"
        >
          MoMa ordering system V1
        </h3>
      </div>
    </div>
    <div v-if="isMobile" class="top-right-mobile">
      <!-- Show the Login and Sign Up buttons if not logged in -->
    </div>
    <div v-else class="top-right">
      <!-- Show the Login  and sign up button if not logged in -->
      <div v-if="!isLoggedIn"> 
        <button @click="showLoginForm">
          Login
        </button>
        <button @click="showRegisterForm">
          Sign Up
        </button>
      </div>
      <!-- Show the Logout button if logged in -->
      <div v-else> 
        <button @click="logout">
          Logout
        </button>
      </div>
    </div>
    <div v-if="!isMobile" class="nav">
      <router-link to="/">
        Home
      </router-link> |
      <router-link to="/about">
        About
      </router-link> |
      <router-link to="/order">
        Order
      </router-link>
    </div>
    <div v-else class="mobile-padding">
      
    </div>
    <router-view />

    <!-- Login Form Overlay -->
    <div 
      v-if="showLogin" 
      class="overlay"
    >
      <div class="login-form">
        <button 
          class="close-button" 
          @click="hideLoginForm"
        >
          X
        </button>
        <h2>
          Login
        </h2>
        <form @submit.prevent="login">
          <div class="form-group">
            <label for="username">
              Username:
            </label>
            <input 
              id="username" 
              v-model="username" 
              type="text" 
              required 
              class="form-input"
            >
          </div>
          <div class="form-group">
            <label for="password">
              Password:
            </label>
            <input 
              id="password" 
              v-model="password" 
              type="password" 
              required 
              class="form-input"
            >
          </div>
          <button 
            type="submit" 
            class="rounded-button"
          >
            Submit
          </button>
        </form>
      </div>
    </div>

    <!-- Register Form Overlay -->
    <div 
      v-if="showRegister" 
      class="overlay"
    >
      <div class="login-form">
        <button 
          class="close-button" 
          @click="hideRegisterForm"
        >
          X
        </button>
        <h2>
          Sign Up
        </h2>
        <form @submit.prevent="register">
          <div class="form-group">
            <label for="newUsername">
              New Username:
            </label>
            <input 
              id="newUsername" 
              v-model="newUsername" 
              type="text" 
              required 
              class="form-input"
            >
          </div>
          <div class="form-group">
            <label for="newPassword">
              New Password:
            </label>
            <input 
              id="newPassword" 
              v-model="newPassword" 
              type="password" 
              required 
              class="form-input"
            >
          </div>
          <button 
            type="submit" 
            class="rounded-button"
          >
            Register
          </button>
        </form>
      </div>
    </div>
  </div>
</template>


<script>
import SideMenu from "./components/SideMenu.vue";

export default {
  components: {
    SideMenu,
  },
  data() {
    return {
      showLogin: false,
      showRegister: false,
      isLoggedIn: false, // Track user login state
      username: '',
      password: '',
      newUsername: '',
      newPassword: '',
      isMobile: false, // Track if it's a mobile device
    };
  },
  methods: {
    showLoginForm() {
      this.showLogin = true;
      this.showRegister = false;
    },
    showRegisterForm() {
      this.showLogin = false;
      this.showRegister = true;
    },
    hideLoginForm() {
      this.showLogin = false;
    },
    hideRegisterForm() {
      this.showRegister = false;
    },
    login() {
      // Simulated login logic (replace with your actual login logic)
      if (this.username === 'your_username' && this.password === 'your_password') {
        alert('Login successful');
        this.isLoggedIn = true; // User is logged in
        this.showLogin = false;
      } else {
        alert('Login failed. Please check your credentials.');
      }
    },
    register() {
      // Simulated registration logic (replace with your actual registration logic)
      alert('Registration successful');
      this.showRegister = false;
    },
    logout() {
      this.isLoggedIn = false; // User logs out
    },
    toggleSideMenu() {
      this.isSideMenuVisible = !this.isSideMenuVisible;
    },
    closeModal() {
      this.isSideMenuVisible = true; // Emit an event to the parent to close the modal
    },
  },
  mounted() {
    // Check if it's a mobile screen (you can adjust the width threshold)
    this.isMobile = window.innerWidth <= 768;

    // Add an event listener to update isMobile on window resize
    window.addEventListener("resize", () => {
      this.isMobile = window.innerWidth <= 768;
    });
  },
};
</script>

<style>
.app {
  font-family: Avenir, Arial, Helvetica, sans-serif;
  text-align: center;
  color: #000000;
  display: flex;
  flex-direction: column;
  justify-content: center;
  align-items: center;
  background-color: #8C9EFF;
}

.top-right {
  position: absolute;
  top: 10px;
  right: 10px;
}

.top-right-mobile {
  position: absolute;
  top: 10px;
  right: 10px;
}

.top-right-mobile button {
  display: block; /* Display buttons as block elements to stack them */
}

.top-left {
  position: absolute;
  top: 10px;
  left: 10px;
}

/* login button  */
button {
  font-weight: bold;
  color: #000000;
  background-color: transparent;
  border: none;
  cursor: pointer;
  padding: 10px;
}

/* navigation bar */
.nav {
  padding: 20px;
}

.nav a {
  font-weight: bold;
  color: #000000;
  text-decoration: none;
  padding: 10px;
  border-radius: 4px;
}

.nav a.router-link-exact-active {
  color: white;
  background: crimson;
}

.card {
  background-color: #ffffff !important;
  color: rgb(0, 0, 0) !important;
}

/* progress bar  */
.progress bar {
  color: #000;
    overflow-x: hidden;
    height: 100%;
    background-repeat: no-repeat;
}

/* Login form */

.overlay {
  position: fixed;
  top: 0;
  left: 0;
  width: 100%;
  height: 100%;
  background: rgba(0, 0, 0, 0.5);
  display: flex;
  justify-content: center;
  align-items: center;
  z-index: 999;
}

.login-form {
  background: white;
  padding: 20px;
  border-radius: 10px; /* Wider border radius for a rounder look */
  box-shadow: 0px 0px 10px rgba(0, 0, 0, 0.2);
  text-align: center;
  position: relative;
  width: 400px; /* Make the login form wider */
}

.close-button {
  position: absolute;
  top: 10px;
  right: 10px;
  background: transparent;
  border: none;
  cursor: pointer;
  font-size: 20px;
}

.form-group {
  display: flex;
  flex-direction: column;
  align-items: flex-start;
  margin-right: 10px; /* Add some margin to the right of the input fields */
}

.form-input {
  width: 100%;
  margin-top: 5px; /* Add some top margin for spacing */
}

.rounded-button {
  border: none;
  background-color: #007BFF;
  color: rgb(0, 0, 0);
  padding: 10px 20px;
  border-radius: 20px;
  cursor: pointer;
  font-weight: bold;
  margin-top: 10px; /* Lower the submit button */
}

/* Hamburger menu button styles */
.hamburger-menu {
  cursor: pointer;
  padding: 10px;
  z-index: 1000; /* Ensure it's on top of other content */
}

.line {
  width: 30px;
  height: 3px;
  background-color: #000;
  margin: 4px 0;
}

.mobile-padding {
  margin-top: 60px;
}
</style>