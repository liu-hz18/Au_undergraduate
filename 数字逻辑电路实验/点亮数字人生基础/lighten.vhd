
LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.std_logic_arith.ALL;
USE ieee.std_logic_unsigned.ALL;

entity lighten is
    port(
        key: in std_logic_vector(3 downto 0); --控制开关
        display: out std_logic_vector(6 downto 0); --不带译码器
        display_4: out std_logic_vector(3 downto 0) --带译码器
    );
end lighten;

architecture bhv of lighten is
begin
    display_4 <= key; --带译码器的可以直接输出开关值, display_4的4个值和key的值完全对应。
    process(key) --不带译码器的需要进行译码处理(进程，顺序执行)，用key给display赋值
    begin
        case key is -- 译码处理
            when "0000" => display <= "1111110";
            when "0001" => display <= "0110000";
            when "0010" => display <= "1101101";
            when "0011" => display <= "1111001";
            when "0100" => display <= "0110011";
            when "0101" => display <= "1011011";
            when "0110" => display <= "0011111";
            when "0111" => display <= "1110000";
            when "1000" => display <= "1111111";
            when "1001" => display <= "1110011";
            when "1010" => display <= "1110111";
            when "1011" => display <= "0011111";
            when "1100" => display <= "1001110";
            when "1101" => display <= "0111101";
            when "1110" => display <= "1001111";
            when "1111" => display <= "1000111";
            when others => display <= "0000000"; --其他情况全灭
        end case;
    end process;
end bhv;

