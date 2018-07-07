<%--
  Created by IntelliJ IDEA.
  User: gaolex
  Date: 18-4-24
  Time: 上午11:15
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>register</title>
</head>
<body>
    <%
        if(request.getAttribute("username").toString().startsWith("user"))
            out.println("该用户名已被注册");
        else if (request.getAttribute("username").toString().equals("admin"))
            out.println("欢迎您，管理员");
        else
            out.println("注册成功");
    %>
</body>
</html>
