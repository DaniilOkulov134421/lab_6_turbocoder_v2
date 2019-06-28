#include <vector>
#include <iostream>

using Bit_t = uint8_t;


class EncoderInterface
{
public:
    virtual void Encode(const std::vector<Bit_t> kInputData, std::vector<Bit_t>& output_data) = 0;
    virtual ~EncoderInterface() {};
};


class ConstituentEncoder : public EncoderInterface
{
public:
    enum OUT_SELECT { ALL, FIRST, SECOND };

    ConstituentEncoder() : m_delay_line{0, 0}, m_select_out(ALL){}
	void Encode(const std::vector<Bit_t> kInputBits, std::vector<Bit_t>& output_bits);
    void PushDelayLine(const Bit_t& in_bit);
    void Reset();
	std::vector<Bit_t> GetDelayLine() const { return m_delay_line; }
    void SelectOut(const OUT_SELECT& kSelectOut){ m_select_out = kSelectOut; }

private:
    std::vector<Bit_t> m_delay_line;
    OUT_SELECT         m_select_out;
};


class Interleaver
{
public:
    void Interleave(const std::vector<Bit_t> kInputBits, std::vector<Bit_t>& output_bits);
    void PushDelayLine(const Bit_t& in_bit);
    void Reset();
    size_t GetLenght() const {  return m_length; }
private:
    size_t m_length = 16;
    std::vector<int> m_table{ 0,3,6,9,12,15,2,5,8,11,14,1,4,7,10,13 };
    std::vector<Bit_t> m_delay_line = std::vector<Bit_t>(16,0);
};


class TurboEncoder : public EncoderInterface
{
private:
    ConstituentEncoder    m_coder_1;
    ConstituentEncoder    m_coder_2;
    Interleaver m_interleaver;
public:
    TurboEncoder();
    bool CheckInputCorrection(const std::vector<uint8_t>& kInputData);
    void Reset();
    void Encode(const std::vector<Bit_t> kInputData, std::vector<Bit_t>& output_bits);
};