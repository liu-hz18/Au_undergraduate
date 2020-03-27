--点亮数字人生, 使用1个不带译码,2个带译码的数码管--
library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

entity lighten2 is 
    port(
        clk: in std_logic; --控制时序变化
        rst: in std_logic; --重置
        display_4: out std_logic_vector(6 downto 0); --Without Decoder
        display_4_odd: out std_logic_vector(3 downto 0); --With Decoder
        display_4_even: out std_logic_vector(3 downto 0) --With Decoder
    );
end lighten2;

architecture bhv of lighten2 is
    component decoder --译码器例化
        port(
            bit_4_vec: in std_logic_vector(3 downto 0);
            bit_7_vec: out std_logic_vector(6 downto 0)
        );
    end component;
    signal display_4_odd_buf: std_logic_vector(3 downto 0) := "0001"; --奇数
    signal display_4_even_buf: std_logic_vector(3 downto 0) := "0000"; --偶数
    signal display_4_buf: std_logic_vector(3 downto 0) := "0000"; --自然数
    signal count: integer := 0; --计数器
begin
    u1: decoder port map(bit_4_vec=>display_4_buf, bit_7_vec=>display_4); --译码
    display_4_even <= display_4_even_buf;--带译码器的直接输出
    display_4_odd <= display_4_odd_buf;  --带译码器的直接输出
    process(clk, rst) begin--时钟控制周期信号
        if rst='1' then --异步复位
            count <= 0;
            display_4_buf <= "0000";--reset
            display_4_even_buf <= "0000";
            display_4_odd_buf <= "0001";
        elsif clk'event and clk='1' then --处在上升沿看，也可以用rising_edge(clk)
            --if count < 1_000_000 then --每1000000次上升，也就是当1MHz(1000ns)时钟频率(注意设置时钟频率)的时候，1s更新1次
            if count < 1 then --仿真的时候简单设为1
                count <= count + 1;
            else
                count <= 0;
                if display_4_buf = "1111" then
                    display_4_buf <= "0000";--重置:F->0
                else
                    display_4_buf <= display_4_buf + 1;--更新自然数
                end if;
                if display_4_even_buf = "1000" then
                    display_4_even_buf <= "0000";--重置:8->0
                else
                    display_4_even_buf <= display_4_even_buf + 2;--更新偶数
                end if;
                if display_4_odd_buf = "1001" then
                    display_4_odd_buf <= "0001";--重置9->1
                else
                    display_4_odd_buf <= display_4_odd_buf + 2;--更新奇数
                end if;
            end if;
        end if;
    end process;
end bhv;
