import { createRouter, createWebHistory } from 'vue-router'
import Home from '../views/HomePage.vue'
import About from '../views/AboutPage.vue'
import Order from '../views/OrderPage.vue'
import { auth } from '../firebase'

const routes = [
  {
    path: '/',
    name: 'Home',
    component: Home
  },
  {
    path: '/about',
    name: 'About',
    component: About
  },
  {
    path: '/order',
    name: 'Order',
    component: Order
  }
]

const router = createRouter({
  history: createWebHistory(process.env.BASE_URL),
  routes
})

router.beforeEach((to, from, next) => {
    if (to.path === '/login' && auth.currentUser) {
        next('/')
        return;
    }

    if (to.matched.some(record => record.meta.requiresAuth) && !auth.currentUser) {
        next('/login')
        return;
    }

    next();
})

export default router