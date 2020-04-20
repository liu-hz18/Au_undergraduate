package fakemenu;
import java.awt.*;
import java.awt.event.*; 
import javax.swing.*;
import java.io.*;

public class FakeMenu extends JFrame{
    MenuBar menubar = new MenuBar();
    Menu menuFile = new Menu("File");
    Menu menuEdit = new Menu("Edit");
    Menu menuWindow = new Menu("Window");
    Menu menuHelp = new Menu("Help");
    public FakeMenu(){
        super("FakeMenu");
        setVisible(true);
        setSize(600, 600);
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        
        menuFile.add(new MenuItem("New"));
        menuFile.add(new MenuItem("Open"));
        menuFile.add(new MenuItem("Save"));
        menuFile.add(new MenuItem("Save As"));
        menubar.add(menuFile);
        menuEdit.add(new MenuItem("Copy"));
        menuEdit.add(new MenuItem("Cut"));
        menuEdit.add(new MenuItem("Paste"));
        menubar.add(menuEdit);
        menubar.add(menuWindow);
        menuHelp.add(new MenuItem("About"));
        menubar.add(menuHelp);
        setMenuBar(menubar);
    }
    public static void main(String[] args){
        FakeMenu app = new FakeMenu();
    }
}
