<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Login Page</title>
    <style>
        * {
            box-sizing: border-box;
            margin: 0;
            padding: 0;
            font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
        }
        body {
            background: linear-gradient(135deg, #667eea, #764ba2);
            height: 100vh;
            display: flex;
            justify-content: center;
            align-items: center;
        }
        .login-container {
            background: #ffffff;
            padding: 40px;
            border-radius: 12px;
            box-shadow: 0 10px 25px rgba(0, 0, 0, 0.2);
            width: 100%;
            max-width: 400px;
        }
        .login-container h2 {
            margin-bottom: 24px;
            color: #333333;
            text-align: center;
        }
        .input-group {
            margin-bottom: 20px;
        }
        .input-group label {
            display: block;
            margin-bottom: 8px;
            color: #555555;
            font-size: 14px;
        }
        .input-group input {
            width: 100%;
            padding: 12px;
            border: 1px solid #cccccc;
            border-radius: 6px;
            font-size: 16px;
            outline: none;
            transition: border-color 0.3s;
        }
        .input-group input:focus {
            border-color: #667eea;
        }
        .btn-submit {
            width: 100%;
            padding: 12px;
            background: #667eea;
            border: none;
            border-radius: 6px;
            color: white;
            font-size: 16px;
            font-weight: bold;
            cursor: pointer;
            transition: background 0.3s;
        }
        .btn-submit:hover {
            background: #5563c1;
        }
        #message {
            margin-top: 15px;
            text-align: center;
            font-size: 14px;
        }
        .error { color: #e74c3c; }
        .success { color: #2ecc71; }
    </style>
</head>
<body>

    <div class="login-container">
        <h2>Welcome Back</h2>
        <form id="loginForm" onsubmit="handleLogin(event)">
            <div class="input-group">
                <label for="username">Username</label>
                <input type="text" id="username" placeholder="Enter your username" required>
            </div>
            <div class="input-group">
                <label for="password">Password</label>
                <input type="password" id="password" placeholder="Enter your password" required>
            </div>
            <button type="submit" class="btn-submit">Login</button>
        </form>
        <div id="message"></div>
    </div>

    <script>
        function handleLogin(event) {
            event.preventDefault(); // Prevent page refresh

            const user = document.getElementById('username').value;
            const pass = document.getElementById('password').value;
            const message = document.getElementById('message');

            // Demo credentials check (You can change these)
            if (user === "admin" && pass === "1234") {
                message.textContent = "Login successful! Redirecting...";
                message.className = "success";
            } else {
                message.textContent = "Invalid username or password! (Hint: admin / 1234)";
                message.className = "error";
            }
        }
    </script>

</body>
</html>
