package simplenotepad;
import java.awt.*;
import java.awt.event.*; 
import javax.swing.*;
import java.io.*;

public class SimpleNotepad extends JFrame{
    JTextArea textArea = new JTextArea("please input your code here");
    MenuBar menubar = new MenuBar();
    Menu menuFile = new Menu("File");
    MenuItem openItem = new MenuItem("Open");
    MenuItem saveItem = new MenuItem("Save");
    Font afont = new Font("Monospaced", Font.PLAIN, 22);
    public SimpleNotepad(){
        super("SimpleNotepad");
        setVisible(true);
        setSize(600, 600);
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        this.getContentPane().setLayout(new BorderLayout());
        openItem.addActionListener(new openFileListener());
        saveItem.addActionListener(new saveFileListener());
        menuFile.add(openItem);
        menuFile.add(saveItem);
        menubar.add(menuFile);
        setMenuBar(menubar);
        initTextArea();
    }

    private class openFileListener implements ActionListener{
        @Override
        public void actionPerformed(ActionEvent e){
            try{
                openFile();
            } catch (Exception err) {
                err.printStackTrace();
            }
        }
    }
    private class saveFileListener implements ActionListener{
        @Override
        public void actionPerformed(ActionEvent e){
            try{
                saveFile();
            } catch (Exception err) {
                err.printStackTrace();
            }
        }
    }
    private void initTextArea(){
        textArea.setLineWrap(true);
        textArea.setFont(afont);
        JScrollPane textareascrollPane = new JScrollPane();
        textareascrollPane.setViewportView(textArea);
        textareascrollPane.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);
        textareascrollPane.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_ALWAYS);
        this.getContentPane().add(textareascrollPane);
        this.getContentPane().add(textareascrollPane, "Center");
    }

    private void openFile() throws Exception{
        FileDialog fd = new FileDialog(this, "Open File", FileDialog.LOAD);
        fd.setVisible(true);
        BufferedReader in = new BufferedReader(new FileReader(fd.getDirectory() + fd.getFile()));
        String str;
        textArea.setText("");//clear
        while((str = in.readLine()) != null){
            textArea.append(str + '\n');
        }
        in.close();
    }

    private void saveFile() throws Exception{
        FileDialog fd = new FileDialog(this, "Save File", FileDialog.SAVE);
        fd.setVisible(true);
        FileOutputStream out = new FileOutputStream(fd.getDirectory() + fd.getFile() + ".txt" );
        out.write(textArea.getText().getBytes());
        out.close();
    }

    public static void main(String[] args){
        SimpleNotepad app = new SimpleNotepad();
    }
}
