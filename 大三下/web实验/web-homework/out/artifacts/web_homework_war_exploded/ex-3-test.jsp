<%--
  Created by IntelliJ IDEA.
  User: gaolex
  Date: 18-4-24
  Time: 上午10:22
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Request与Response对象的应用</title>
</head>
<body>
    <p>太原理工大学的校庆日是</p>
    <form action="ex-3-answer.jsp" method="post">
        <input type="radio" name="choose" value="5-1">5月1日
        <input type="radio" name="choose" value="5-2">5月2日
        <input type="radio" name="choose" value="5-3">5月3日
        <input type="radio" name="choose" value="5-4">5月4日<br>
        <input type="submit" value="提交答案">
    </form>
</body>
</html>
