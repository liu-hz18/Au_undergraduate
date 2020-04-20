package colorword;
import java.awt.*;
import java.awt.event.*; 
import javax.swing.*;
import java.io.*;

public class ColorWord extends JFrame{
    JTextField field = new JTextField(10);
    JButton butRed = new JButton("Red");
    JButton butYellow = new JButton("Yellow");
    JButton butPurple = new JButton("Purple");
    JPanel buttonPanel=new JPanel();
    Color purple = new Color(150,0,150);
    //create button actions 
    ColorAction redAction = new ColorAction(Color.RED);
    ColorAction yellowAction = new ColorAction(Color.YELLOW);
    ColorAction purpleAction = new ColorAction(purple);
    Dimension buttonSize = new Dimension(150, 80);//设置尺寸
    Font afont = new Font("Monospaced", Font.BOLD, 24);
    
    public ColorWord(){
        super("ColorWord");
        this.setLayout(new GridLayout(2, 1, 50, 50));
        
        setButton(butRed, Color.RED, redAction);
        setButton(butYellow, Color.YELLOW, yellowAction);
        setButton(butPurple, purple, purpleAction);

        setTextField("Hello Java World!", Color.BLACK);
        
        add(buttonPanel);
        add(field);
        
        setSize(600, 600);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setVisible(true);
    }
    private void setButton(JButton button, Color c, ColorAction action){
        button.setPreferredSize(buttonSize);
        button.setFont(afont);
        button.setForeground(c);
        button.addActionListener(action);
        buttonPanel.add(button);
    }
    private void setTextField(String initText, Color c){
        field.setText(initText);
        field.setForeground(c);
        field.setFont(afont);
        field.setHorizontalAlignment(JTextField.CENTER);
    }
    private class ColorAction implements ActionListener{
        private Color fontColor;
        public ColorAction(Color c){
            fontColor = c;
        }
        public void actionPerformed(ActionEvent e){
            field.setForeground(fontColor);
        }
    }
    public static void main(String[] args){
        ColorWord app = new ColorWord();
    }
}