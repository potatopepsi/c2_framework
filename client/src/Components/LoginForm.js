import React, { useState } from "react";

function LoginForm() {
  const [username, setUsername] = useState("");
  const [password, setPassword] = useState("");

  const [isLoading, setIsLoading] = useState(false);
  const [error, setError] = useState("");
  const [message, setMessage] = useState("");

  let handleSubmit = async (e) => {
    e.preventDefault();
    setIsLoading(true);
    try {
      let response = await fetch("http://127.0.0.1:5000/login", {
        method: "POST",
        mode: "cors",
        body: new URLSearchParams({
          username: username,
          password: password,
        }),
        headers: {
          "Content-Type": "application/x-www-form-urlencoded",
        },
      });
      let data = await response.json();
      console.log("access_code: " + Object.keys(data));

      if (response.status === 200) {
        setMessage("Login succesful");
      } else if (response.status === 401) {
        setMessage("Wrong username or password");
      } else {
        setMessage("Error logging in");
      }
    } catch (error) {
      setError(error.message);
    } finally {
      setIsLoading(false);
    }
  };

  if (isLoading) return <div>Loading...</div>;
  if (error) return <div>error: {error}</div>;
  return (
    <div>
      <div>{message}</div>
      <form onSubmit={handleSubmit}>
        <label>
          username:
          <input
            name="username"
            type="text"
            value={username}
            onChange={(e) => setUsername(e.target.value)}
          />
        </label>
        <br />
        <label>
          password:
          <input
            name="password"
            type="text"
            value={password}
            onChange={(e) => setPassword(e.target.value)}
          />
        </label>
        <button type="submit">Login</button>
      </form>
    </div>
  );
}

export default LoginForm;
