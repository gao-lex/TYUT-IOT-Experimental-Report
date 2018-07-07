<%--
  Created by IntelliJ IDEA.
  User: gaolex
  Date: 18-4-24
  Time: 上午10:29
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>answer</title>
</head>
<body>
    <%
        String ans = request.getParameter("choose");
        if (ans.equals("5-4"))
            response.sendRedirect("ex-3-yes.jsp");
        else
            response.sendRedirect("ex-3-no.jsp");
    %>
</body>
</html>
