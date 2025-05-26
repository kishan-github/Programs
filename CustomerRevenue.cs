/*
 * Write below api's :
 * addRevenue(revenue) - create a customer with revenue as given.
 * addRevenue(revenue, refferedBy) - create a customer with revenue as given and update the reveue of refferedBy customer by adding revenue.
 * getKCustomersWithRevenueMoreThanGiven(k, revenue) - Return k customer id's that have revenue greater than revenue.
 */

using System;

Console.WriteLine("Start executing main.....");
var revenueManager = new RevenueManager();
int cust1 = revenueManager.addRevenue(50);                      // 90
int cust2 = revenueManager.addRevenue(40, cust1);               // 100
int cust3 = revenueManager.addRevenue(60, cust2);               // 60
var list = revenueManager.getKCustomersWithRevenueMoreThanGiven(2, 55);

foreach (var item in list)
{
    Console.WriteLine(item);
}
// TreeNode
public class TreeNode
{
    public Customer CustomerObj;

    public TreeNode? Left;

    public TreeNode? Right;

    public TreeNode(Customer obj)
    {
        CustomerObj = obj;
    }
}

public class BST
{
    // Add node to BST based on revenue
    public TreeNode AddNode(TreeNode root, Customer obj)
    {
        if (root == null)
        {
            return new TreeNode(obj);
        }

        if (obj.Revenue > root.CustomerObj.Revenue)
            root.Right = AddNode(root.Right, obj);
        else
            root.Left = AddNode(root.Left, obj);

        return root;
    }

    // Delete node
    public TreeNode DeleteNode(TreeNode root, Customer obj)
    {
        if (root == null)
            return null;

        if (obj.Revenue < root.CustomerObj.Revenue)
            root.Left = DeleteNode(root.Left, obj);
        else if (obj.Revenue > root.CustomerObj.Revenue)
            root.Right = DeleteNode(root.Right, obj);
        else
        {
            if (root.Left == null && root.Right == null)
                return null;

            if (root.Left == null)
                return root.Right;
            if (root.Right == null)
                return root.Left;

            var successor = GetInorderSuccessor(root.Right);
            root.CustomerObj = successor.CustomerObj;
            root.Right = DeleteNode(root.Right, successor.CustomerObj);
        }

        return root;
    }

    private TreeNode GetInorderSuccessor(TreeNode root)
    {
        while (root.Left != null)
            root = root.Left;

        return root;
    }
}

public class Customer
{
    public int CustomerId;

    public int Revenue;

    public Customer(int customerId, int revenue)
    {
        this.CustomerId = customerId;
        this.Revenue = revenue;
    }
}

public class RevenueManager
{
    private int _customerId;

    private List<Customer> CustomerList = new();

    private TreeNode? Root;

    private BST bst = new BST();

    public RevenueManager()
    {
        _customerId = 1;
    }

    public int addRevenue(int revenue)
    {
        // Create new customer, add it to List and BST.
        var customer = new Customer(_customerId, revenue);
        CustomerList.Add(customer);
        Root = bst.AddNode(Root, customer);
        _customerId++;
        return customer.CustomerId;
    }

    public int addRevenue(int revenue, int refferedBy)
    {
        // Create new customer, add it to List and BST.
        var customer = new Customer(_customerId, revenue);
        CustomerList.Add(customer);
        Root = bst.AddNode(Root, customer);

        // Remove refferedBy node from tree as its revenue now would be updtaed.
        Root = bst.DeleteNode(Root, CustomerList[refferedBy - 1]);

        // Update the revenue of the refferedBy custmer and again add it to BST.
        CustomerList[refferedBy - 1].Revenue += revenue;
        Root = bst.AddNode(Root, CustomerList[refferedBy - 1]);
        _customerId++;
        return customer.CustomerId;
    }

    public List<int> getKCustomersWithRevenueMoreThanGiven(int k,  int revenue)
    {
        var list = new List<int>();
        getCustomersFromTree(Root, k, revenue, list);
        return list;
    }

    private void getCustomersFromTree(TreeNode root, int k, int revenue, List<int> list)
    {
        if (root == null || list.Count >= k) 
            return;

        // If curr revenue is greater, we can continue traversing left tree.
        if (root.CustomerObj.Revenue > revenue)
        {
            getCustomersFromTree(root.Left, k, revenue, list);
        }

        // If curr revenue is greater and list is not full then add it to list.
        if (root.CustomerObj.Revenue > revenue && list.Count < k)
        {
            list.Add(root.CustomerObj.CustomerId);
        }

        // Go to right tree if list is still not full.
        if (list.Count < k)
        {
            getCustomersFromTree(root.Right, k, revenue, list);
        }
    }
}
