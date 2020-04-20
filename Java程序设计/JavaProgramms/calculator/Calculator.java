
package calculator;
import java.awt.*;
import java.awt.event.*; 
import javax.swing.*;
import java.io.*;
import java.util.Stack;
import java.util.Queue;
import java.util.ArrayList;

public class Calculator extends JFrame implements ActionListener{
    Stack<Node> op = new Stack<Node>();
    ArrayList<Node> rpn = new ArrayList<Node>();
    private String[] keys = {"(", ")", "C", "<-", 
                             "7", "8", "9", "+",
                             "4", "5", "6", "-",
                             "1", "2", "3", "*",
                             ".", "0", "=", "/"};
    JTextField text = new JTextField("");
    JButton[] button = new JButton[keys.length];
    Font afont = new Font("Monospaced", Font.PLAIN, 22);
    String expression = "";

    public class Node{
        public boolean isOp;
        public Float number;
        public char op = '%';
        public Node(Float num){
            isOp = false;
            number = num;
        }
        public Node(char opr, boolean dummy){
            isOp = true;
            op = opr;
        }
        public String toString(){
            if(isOp)return String.valueOf(op);
            else return number.toString();
        }
    }

    public Calculator(){
        super("Calculator");
        setVisible(true);
        setSize(600, 800);
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        text.setFont(afont);
        JPanel keyPanel = new JPanel(); 
        keyPanel.setLayout(new GridLayout(6, 1));
        keyPanel.add(text);
        Container[] containers = new Container[5];
        for (int i = 0;i < 5;++i){
            containers[i] = new Container();
            containers[i].setLayout(new GridLayout(1, 4));
            keyPanel.add(containers[i]);
        }
        for (int i = 0; i < button.length; i++){
            button[i] = new JButton(keys[i]);
            button[i].setFont(new Font("Monospaced", Font.BOLD, 30));
            containers[i / 4].add(button[i]);
            button[i].addActionListener(this);
            if (i == 2 || i == 3) button[i].setForeground(Color.red);
        }
        getContentPane().add(keyPanel);
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        String action = e.getActionCommand();
        if (action.equals(keys[2])) {
            expression = "";
            text.setText("");
        } else if (action.equals(keys[3])) {
            expression = expression.substring(0, expression.length()-1);
            text.setText(expression);
        } else if (action.equals(keys[18])) {
            System.out.println(expression);
            text.setText(calExpresstion(expression));
            expression = "";
        } else {
            expression += action;
            text.setText(expression);
        }
    }
    public static float cal(char op, float num1, float num2){
        if (op == '+') return num2 + num1;
        else if (op == '-') return num2 - num1;
        else if (op == '*') return num2 * num1;
        else if (op == '/') return num2 / num1;
        else return 0.0f;
    }
    public String calExpresstion(String exp){
        char[] expr = exp.toCharArray();
        op.clear();
        rpn.clear();
        for(int i = 0; i < expr.length;){
            char ch = expr[i];
            if(ch >= '0' && ch <= '9'){
                Float temp = 0.0f;
                while(i < expr.length && expr[i] >= '0' && expr[i] <= '9'){
                    temp = temp * 10.0f + Float.valueOf(expr[i] - '0');
                    i += 1;
                }
                rpn.add(new Node(temp));
            } else if (ch == '(') {
                op.push(new Node(ch, false));
                i += 1;
            } else if (ch == '+' || ch == '-') {
                while (!op.empty() && (op.peek().op != '('))rpn.add(op.pop());
                op.push(new Node(ch, false));
                i += 1;
            } else if (ch == '*' || ch == '/') {
                while (!op.empty() && (op.peek().op == '*' || op.peek().op == '/'))rpn.add(op.pop());
                op.push(new Node(ch, false));
                i += 1;
            } else if (ch == ')') {
                while (!op.empty() && op.peek().op != '(')rpn.add(op.pop());
                op.pop();
                i += 1;
            }
        }
        while(!op.empty())rpn.add(op.pop());
        System.out.println(rpn.toString());
        return calRpn();
    }
    public String calRpn(){
        Stack<Float> numStack = new Stack<Float>();
        for(int i = 0; i < rpn.size(); i++){
            Node temp = rpn.get(i);
            if (temp.isOp) {
                numStack.push(cal(temp.op, numStack.pop(), numStack.pop()));
            } else {
                numStack.push(temp.number);
            }
        }
        return numStack.pop().toString();
    }
    public static void main(String[] args){
        Calculator app = new Calculator();
    }
}
