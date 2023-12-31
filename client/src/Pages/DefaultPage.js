import { useEffect, useState } from "react";
import { Navigate, Outlet } from "react-router-dom";
import "spectre.css";
import AuthService from "../Components/AuthService";
import NavBar from "../Components/NavBar";

function DefaultPage() {
  const [isLoggedIn, setIsLoggedIn] = useState();

  function checkState() {
    const someBool = AuthService.isLoggedIn();
    setIsLoggedIn(someBool);
  }
  
  useEffect(() => {
    checkState();
  }, []);
  
  if (isLoggedIn === false) {
    return <Navigate to="/login" />;
  }
  return (
    <div>
      <NavBar setLogin={setIsLoggedIn}/>
      <Outlet />
    </div>
  );
}

export default DefaultPage;
