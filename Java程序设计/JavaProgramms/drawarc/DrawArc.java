package drawarc;
import java.awt.*;
import javax.swing.*;
import java.io.*;

public class DrawArc extends JFrame{
    public DrawArc(){
        super("DrawArc");
        setVisible(true);
        setSize(600, 600);
    }
    //overwrite paint method
    public void paint(Graphics g){
        super.paint(g);
        //draw text
        g.setFont(new Font("Monospaced", Font.ITALIC, 24));
        g.drawString("Welcome to Java world", 100, 550);
        int centerx = 300, centery = 200, r = 150, angle = 30, startAngle = 30;
        //draw pole
        g.setColor(Color.GREEN);
        g.fillRect(centerx-5, centery-5, 10, 300);
        //draw fan
        g.setColor(Color.BLUE);
        g.fillArc(centerx-r, centery-r, 2*r, 2*r, startAngle, angle);
        g.fillArc(centerx-r, centery-r, 2*r, 2*r, startAngle + 3*angle, angle);
        g.fillArc(centerx-r, centery-r, 2*r, 2*r, startAngle + 6*angle, angle);
        g.fillArc(centerx-r, centery-r, 2*r, 2*r, startAngle + 9*angle, angle);
    }
    public static void main(String[] args) {
        DrawArc app = new DrawArc();
        app.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }
}