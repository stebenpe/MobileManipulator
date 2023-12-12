# Website
De website voor de MoMa is het ordersysteem van de koffie.
In dit geval runt de website en ros2 op dezelfde embedded AI computer. (Jetson AGX orin)

## 1. Project setup
Als het nodig is kan je in de config.json de WS_URL aanpassen.
Dit is het IP-adress van de (embedded) computer waar de ros2 server op draait.
Deze is nu ingesteld volgens het [netwerk overzicht](https://github.com/stebenpe/MobileManipulator#Netwerk). 

ga naar de vue-webpannel map
```
npm install
```

Compile en start de server vervolgens met:
```
npm run serve
```
## 2. Bestanden

De hoofd pagina van de website is te zien in de App.vue in de src map.

De sub pagina's zijn te vinden in de src/views map.
Dit zijn:
1. AboutPage.vue
2. HomePage.vue
3. OrderPage.vue.

Deze sub pagina's zijn gelinkt in de router. Deze is is te vinden in de src/router map.


Ook zijn er child components gemaakt voor het overzicht en omdat somige meerdere keren worden laten zien. Deze componenten zijn te vinden in de src/components map.
Dit zijn:
1. MapSelection.vue
2. OrderProduct.vue
3. ProductOptionModal.vue
4. ProgressBar.vue
5. RecognitionSensorDisplay.vue
6. SideMenu.vue
7. TestBridgeComponent.vue
8. VideoComponent.vue

## 3. Hoofd pagina
De hoofdpagina is de app.vue. Dit is de basis van de website en is op elke pagina te zien.
Hierin zit het menu van de site voor de pagina's en de login/logout. 



### 3.1 Menu bar
Op de hoofdpagina zit een link naar de sub pagina's. Dit gaat als volgt:

```HTML
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
```

Voor de telefoon is er een hamburger menu gemaakt. dit ziet er als volgt uit
```HTML
<div v-if="isMobile">
    <div @click="openMenu" class="hamburger-menu">
        <div class="line"></div>
        <div class="line"></div>
        <div class="line"></div>
    </div>
    <SideMenu v-if="isSideMenuVisible" :is-visible="isSideMenuVisible" @logout="logout" />
</div>
```

### 3.2 Login/logout
De login/logout is bedoeld om uiteindelijk met google firebase te werken maar dit is nog niet geinplementeerd.
Voor nu ziet dit er als volgt uit.

De knoppen voor in en uitloggen laten zien:
```HTML
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
```

De overlay voor de login zier er weer als volgt uit:
```HTML
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
```

Het JS meganisme hier achter is nu gesimuleerd met een gedevinieerde gebruikersnaam en wachtwoord. Dit wordt later nog aangepast door middel van google firebase.
```JS
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
```

## 4. sub pagina's
De sub pagina's worden bij de App.vue weergegeven door de volgende lijn:
```HTML
<router-view />
```
Dit zijn de volgende pagina's: 


### 4.1 Home
De home pagina is de pagina die als eerst voor komt bij het openen van de site.

#### 4.1.1 Stats
Op deze pagina zijn de stats van de robot te zien op de site:
```HTML
<div class="card text-center col-12 mt-1 w-100">
    <RecognitionSensorDisplay>
    </RecognitionSensorDisplay>
</div>
```

#### 4.1.2 Progress
De progress bar van de gemaakte order. Hierbij is ook een link naar de child component voor de data die van ros2 binnen komt in de home page:
```HTML
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
```
De data wat wordt opgehaald uit de robot gaat via een websocket. Dit gaat als volgt.
Eerst word de roslib library geimporteerd:
```JS
import * as ROSLIB from 'roslib';
```
Vervolgens wordt er een data component aangemaakt genaamd retrievedData voor de inkomende data:
```JS
data() {
    return {
        retrievedData: {},
    };
},
```
De data komt binnen via een websocket connectie welke in stand wordt gebracht bij het creeeren/openen van de site.
```JS
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
```

#### 4.1.3 Iframe en video
Een iframe en video component. Hierbij is de iframe meer een test en zal deze in de toekomst worden gebruikt voor de 3D visualisatie van de robot:
```HTML
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
```

#### 4.1.4 Test bridge
En als laatste de testbridge component:
```HTML
<div class="card col-12 mt-1 w-100">
    <TestBridgeComponent />
</div>
```


### 4.2 About
Op de about pagina staat de hoofdpagina van deze github repo

### 4.3 Order
Op de order pagina zijn alle drankje te zien welke besteld kunnen worden. deze worden gecreerd door het OrderProduct.vue component meerdere keren aan te maken maar met verschilende data:
```HTML
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
```
In de order pagina zit ook een handleOrder JS functie voor het sturen van de gemaakte order over de websocket:
```JS
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
```

## 5. components
Zoals hierboven te zien is zijn er een aantal child components die in de verschilende pagina's worden gebruikt. Deze worden hier uitgelegd:

### 5.1 Map selection
De map selection is een overlay dat over de pagina word weergegeven. De map selection wordt geopent zodra er word geklikt op "select on Map" bij het product option menu.
De map wordt weergegeven met een .png en is op bepaalde plekken klikbaar door middel van een map area, deze foto met area's wordt ook aangepast als deze op een telefoon wordt weergegeven:
```HTML
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
```
De coordinaten van de click area's worden doorgegeven met de volgende functie:
```JS
getCoords(room) {
    const coordinates = {
        PLC: [34,200,250,350],
        docenten: [500,150, 630,250],
        studie_landschap: [400,300, 750,400],
        elektro_hoek: [1050,150,1175,250],
    };
    return coordinates[room].map((coord) => (this.isMobile ? coord / 2.75: coord)).join(',');
},
```

### 5.2 Order product
De order product laat een te bestellen drankje zien met een foto, naam, calorieen en een order knop.

De foto's worden als volgt laten zien:
```HTML
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
```
de naam en calorieen als volgt:
```HTML
<h2>{{ name }}</h2>
<p class="calories">
    Calories: {{ calories }}
</p>
```
De order knop met een variabele welke de order opties kan laten zien
```HTML
<button 
    class="order-button" 
    @click="showModal = true"
>
    Order
</button>
```
Het child component dat de opties van het drankje laat zien zoals sterkte en suiker. Hier zit weer de handle order functie gelinkt welke weer naar de order pagina wordt gelinkt:
```HTML
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
```

### 5.3 Product option
In de product option component zijn de mogelijke opties van de drankjes te zien. Dit is per drankje weer anders, bij koffie heb je suiker en sterkte en bij chocolade melk niks. Dit is gedaan door de volgende if statements:
```HTML
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
```
Vervolgens is de map selectie hierin gekoppeld door de volgende manier:
```HTML
<map-selection @roomnr="selectRoom"></map-selection>
```
De geselecteerde opties van het drankje worden vervolgen weer naar het parent component gelinkt door middel van de volgende functie:
```JS
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
```

### 5.4 Progress bar
De progress bar laat de huidige status van de bestelling zien. Dit laat de E.T.A. zien:
```HTML
<p 
  class="mb-0"
>
  E.T.A <span>{{ eta_min }} min, {{ eta_sec }} sec</span>
</p>
```
Verder heeft deze een blauwe bar welke afhankelijk van de state voller is. Dit wordt op de volgende manier gedaan:
```HTML
<ul 
  id="progressbar" 
  class="text-center"
>
    <li 
        :class="{ 'active': state >= 0 }" 
        class="step0"
    >
    </li>
    <li 
        :class="{ 'active': state >= 1 }" 
        class="step0"
    >
    </li>
    <li 
        :class="{ 'active': state >= 2 }" 
        class="step0"
    >
    </li>
    <li 
        :class="{ 'active': state >= 3 }" 
        class="step0"
    >
    </li>
</ul>
```
Vervolgens worden logo's eronder weergegeven van de statusen order gemaakt, robot onderweg, de koffie wordt gezet en aangekomen. Dit wordt als volgt gedaan:
```HTML
<div class="row justify-content-between top">
    <div class="col-md-3 col-sm-6 col-6 icon-content">
        <div class="d-flex flex-column align-items-center">
            <img 
              class="icon" 
              src="../images/ordered.png"
            >
            <p :class="font-weight-bold">
              Order Processed
            </p>
          </div>
        </div>
        <div class="col-md-3 col-sm-6 col-6 icon-content">
          <div class="d-flex flex-column align-items-center">
            <img 
              class="icon" 
              src="../images/driving-robot.png"
            >
            <p :class="font-weight-bold">
              Robot on its way
            </p>
          </div>
        </div>
        <div class="col-md-3 col-sm-6 col-6 icon-content">
          <div class="d-flex flex-column align-items-center">
            <img 
              class="icon" 
              src="../images/coffee-being-made.png"
            >
            <p :class="font-weight-bold">
              Pouring {{ drink }}
            </p>
          </div>
        </div>
        <div class="col-md-3 col-sm-6 col-6 icon-content">
          <div class="d-flex flex-column align-items-center">
            <img 
              class="icon" 
              src="../images/hot-drink.jpg"
            >
            <p :class="font-weight-bold">
              {{ drink }} Arrived
            </p>
          </div>
        </div>
    </div>
</div>
```
De progress bar is ook zo gemaakt dat hij de indeling veranderd op een telefoon.
### 5.5 Sensors
De robot stats worden weergegeven door het sensor component. Dit wordt gedaan door middel van een tabel en gaat als volgt:
```HTML
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
```

### 5.6 Side menu
De side menu wordt alleen weergegeven op een telefoon. Deze is nu nog heel simpel gemaakt maar wordt in de toekomst wel nog aangepast. Het ziet er nu als volgt uit:
```HTML
<div class="side-menu" :class="{ 'menu-visible': isVisible }">
    <router-link to="/">Home</router-link>
    <router-link to="/about">About</router-link>
    <router-link to="/order">Order</router-link>
    <button @click="logout">Logout</button>
</div>
```

### 5.7 Test bridge
De test bridge is er om een connectie met ros2 te controlleren. Deze geeft alle data weer van veranderingen in ros2 nodes, topics en services. Dit gaat als volgt:
```HTML
<div>
    <h1>Latest EventWindow</h1>
    <json-pretty 
      :key="retrievedData" 
      :data="retrievedData"
    >
    </json-pretty>
</div>
```

### 5.8 Video
Het video component moet uiteindelijk een live beeld van de camera op de robot laten zien. Op dit moment is deze nog niet getest en afgemaakt.