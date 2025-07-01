USE Northwind
GO

CREATE VIEW PedidosProductos1997_123456789 AS
SELECT 
    P.ProductName,
    O.OrderDate,
    O.ShippedDate,
    (OD.UnitPrice * OD.Quantity) AS Subtotal
FROM Orders AS O
INNER JOIN [Order Details] AS OD ON O.OrderID = OD.OrderID
INNER JOIN Products AS P ON OD.ProductID = P.ProductID
WHERE YEAR(O.OrderDate) = 1997
ORDER BY P.ProductName;
