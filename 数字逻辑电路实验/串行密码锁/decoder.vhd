-- Show the number input in LED --
library ieee;
use ieee.std_logic_1164.all;

entity decoder is
    port(
        bit_4_vec: in std_logic_vector(3 downto 0);
        bit_7_vec: out std_logic_vector(6 downto 0)
    );
end decoder;

architecture bhv_decode of decoder is
begin
    process(bit_4_vec) begin
        case bit_4_vec is --译码处理
            when "0000" => bit_7_vec <= "1111110";
            when "0001" => bit_7_vec <= "0110000";
            when "0010" => bit_7_vec <= "1101101";
            when "0011" => bit_7_vec <= "1111001";
            when "0100" => bit_7_vec <= "0110011";
            when "0101" => bit_7_vec <= "1011011";
            when "0110" => bit_7_vec <= "1011111";
            when "0111" => bit_7_vec <= "1110000";
            when "1000" => bit_7_vec <= "1111111";
            when "1001" => bit_7_vec <= "1110011";
            when "1010" => bit_7_vec <= "1110111";
            when "1011" => bit_7_vec <= "0011111";
            when "1100" => bit_7_vec <= "1001110";
            when "1101" => bit_7_vec <= "0111101";
            when "1110" => bit_7_vec <= "1001111";
            when "1111" => bit_7_vec <= "1000111";
            when others => bit_7_vec <= "0000000"; --其他情况全灭
        end case;
    end process;
end bhv_decode;