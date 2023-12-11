/* eslint-disable padded-blocks */
import { initializeApp } from "firebase/app";
// import { getAnalytics } from "firebase/analytics";
import { getAuth } from "firebase/auth"

const firebaseConfig = {
  apiKey: "AIzaSyBfgkwD2hRdKQMzTapzna6v0ZSZ0Gmmd2k",
  authDomain: "moma-ordering-login.firebaseapp.com",
  projectId: "moma-ordering-login",
  storageBucket: "moma-ordering-login.appspot.com",
  messagingSenderId: "652963837870",
  appId: "1:652963837870:web:ab9babb58da634dd097a3f",
  measurementId: "G-J832GZ6YWM"
};

// Initialize Firebase
const app = initializeApp(firebaseConfig);
// const analytics = getAnalytics(app);
const auth = getAuth(app);

export { auth }
