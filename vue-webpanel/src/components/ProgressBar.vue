<template>
  <div class="order tracking">
    <div class="card">
      <div class="row d-flex justify-content-between px-3 top">
        <div class="d-flex">
          <h5>Order nr <span class="text-primary font-weight-bold">{{ ordernr }}</span></h5>
        </div>
        <div class="d-flex flex-column text-sm-right">
          <p 
            class="mb-0"
          >
            E.T.A <span>{{ eta_min }} min, {{ eta_sec }} sec</span>
          </p>
        </div>
      </div>
      <!-- Add class 'active' to progress -->
      <div class="row d-flex justify-content-center">
        <div class="col-12">
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
        </div>
      </div>
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
  </div>
</template>  

<script>
export default {
  props: {
    ordernr: String,
    state: Number,
    drink: String,
    eta_min: Number,
    eta_sec: Number,
  },
};
</script>

<style scoped>
body {
    color: #000;
    overflow-x: hidden;
    height: 100%;
    background-color: #8C9EFF;
    background-repeat: no-repeat;
}
.card {
    z-index: 0;
    background-color: #ECEFF1;
    padding-bottom: 20px;
    margin-top: 15px;
    margin-bottom: 15px;
    border-radius: 10px;
}

.top {
    padding-top: 40px;
    padding-left: 13% !important;
    padding-right: 13% !important;
}

/*Icon progressbar*/
#progressbar {
    margin-bottom: 30px;
    overflow: hidden;
    color: #455A64;
    padding-left: 0px;
    margin-top: 30px;
} 

#progressbar li {
    list-style-type: none;
    font-size: 13px;
    width: 25%;
    float: left;
    position: relative;
    font-weight: 400;
}

#progressbar .step0:before {
    font-family: FontAwesome;
    content: "\f10c";
    color: #fff;
}

#progressbar li:before {
    width: 40px;
    height: 40px;
    line-height: 45px;
    display: block;
    font-size: 20px;
    background: #C5CAE9;
    border-radius: 50%;
    margin: auto;
    padding: 0px;
}

/*ProgressBar connectors*/
#progressbar li:after {
    content: '';
    width: 100%;
    height: 12px;
    background: #C5CAE9;
    position: absolute;
    left: 0;
    top: 16px;
    z-index: -1;
}

#progressbar li:last-child:after {
    border-top-right-radius: 10px;
    border-bottom-right-radius: 10px;
    position: absolute;
    left: -50%;
}

#progressbar li:nth-child(2):after, #progressbar li:nth-child(3):after {
    left: -50%;
}

#progressbar li:first-child:after {
    border-top-left-radius: 10px;
    border-bottom-left-radius: 10px;
    position: absolute;
    left: 50%;
}

#progressbar li:last-child:after {
    border-top-right-radius: 10px;
    border-bottom-right-radius: 10px;
}

#progressbar li:first-child:after {
    border-top-left-radius: 10px;
    border-bottom-left-radius: 10px;
}

/*Color number of the step and the connector before it*/
#progressbar li.active:before, #progressbar li.active:after {
    background: #651FFF;
}

#progressbar li.active:before {
    font-family: FontAwesome;
    content: "\f00c";
}

.icon {
    width: 120px;
    height: 120px;
    margin-right: 15px;
    object-fit: cover;
}

.icon-content { 
    padding-bottom: 20px;
}

@media screen and (max-width: 992px) {
    .icon-content {
        width: 50%;
    }
}
</style>