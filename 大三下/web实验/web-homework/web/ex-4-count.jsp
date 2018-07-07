<%--
  Created by IntelliJ IDEA.
  User: gaolex
  Date: 18-4-24
  Time: 上午10:44
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>网页计数器</title>
</head>
<body>
    <%!
        synchronized void countPeople(){
            Integer number = (Integer)application.getAttribute("counter");
            if(number == null)
            {
                number = new Integer(1);
                application.setAttribute("count",number);
            }
            else{
                number = new Integer(number.intValue()+1);
                application.setAttribute("count",number);
            }
        }
    %>
    <%--<%--%>
        <%--if(application.getAttribute("counter")==null)--%>
            <%--application.setAttribute("counter","1");--%>
        <%--else{--%>
            <%--String strnum = null;--%>
            <%--strnum = application.getAttribute("counter").toString();--%>
            <%--int icount = 0;--%>
            <%--icount = Integer.valueOf(strnum).intValue();--%>
            <%--icount++;--%>
            <%--application.setAttribute("count",Integer.toString(icount));--%>
        <%--}--%>
    <%--%>--%>
    <%
        if(session.isNew())
            countPeople();
        Integer yourNUmber = (Integer)application.getAttribute("count");
    %>
    <%--<p>您是第<%=application.getAttribute("counter")%>位访问者</p>--%>
    <p>您是第<%=yourNUmber%>位访问者</p>
</body>
</html>
