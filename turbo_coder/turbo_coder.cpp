#include "turbo_coder.h"

void ConstituentEncoder::Encode(const std::vector<Bit_t> kInputBits, std::vector<Bit_t>& output_bits)
{
	for (auto &in_bit : kInputBits) {
        Bit_t sum_1 = in_bit ^ m_delay_line.at(0) ^ m_delay_line.at(1);
		Bit_t sum_2 = sum_1 ^ m_delay_line.at(1);
        PushDelayLine(sum_1);

        if(m_select_out == ALL)
        {
            output_bits.push_back(in_bit);
            output_bits.push_back(sum_2);
        }
        else if (m_select_out == FIRST)
        {
            output_bits.push_back(in_bit);
        }
        else if (m_select_out == SECOND)
        {
            output_bits.push_back(sum_2);
        }
	}
}

void ConstituentEncoder::PushDelayLine(const Bit_t& in_bit)
{
    if (in_bit > 1) throw "Error ConstituentEncoder! Invalid bit value {0, 1}!\n";
    m_delay_line.insert(m_delay_line.begin(), in_bit);
    m_delay_line.pop_back();
}

void ConstituentEncoder::Reset()
{
    m_delay_line.clear();
    m_delay_line = { 0, 0 };
}


void Interleaver::PushDelayLine(const Bit_t& in_bit)
{
    if (in_bit > 1) { std::cerr << "PushDelayLine: Error! Invalid bit value!\n"; exit(1); }
    m_delay_line.insert(m_delay_line.begin(), in_bit);
    m_delay_line.pop_back();
}

void Interleaver::Reset()
{
    m_delay_line.clear();
    m_delay_line = std::vector<Bit_t>(m_length, 0);
}

void Interleaver::Interleave(const std::vector<Bit_t> kInputBits, std::vector<Bit_t>& output_bits)
{
	for (size_t it = 0; it < kInputBits.size(); it += m_length) {
		for (size_t bit = 0; bit < m_length; ++bit) {
			m_delay_line.at(bit) = kInputBits.at(it + bit);
		}

		for (int it = 0; it < m_length; ++it) {
			output_bits.push_back( m_delay_line.at(m_table.at(it)) );
		}
	}
}

TurboEncoder::TurboEncoder()
{
    m_coder_1.SelectOut(ConstituentEncoder::ALL);
    m_coder_2.SelectOut(ConstituentEncoder::SECOND);
}

bool TurboEncoder::CheckInputCorrection(const std::vector<uint8_t>& kInputData)
{
    for (size_t it = 0; it < kInputData.size(); ++it)
    {
        if (kInputData.at(it) > 1) return 0;
    }
    return 1;
}

void TurboEncoder::Reset()
{
    m_coder_1.Reset();
    m_coder_2.Reset();
    m_interleaver.Reset();
}

void TurboEncoder::Encode(std::vector<Bit_t> kInputData, std::vector<Bit_t>& output_bits)
{
    if (!CheckInputCorrection(kInputData)) throw "Error : Input elements must be 0 or 1\n";

    std::vector<uint8_t> input_corrected(kInputData);
    int block_size = m_interleaver.GetLenght();
    int corrected_size = (kInputData.size() % block_size == 0) ? kInputData.size() : ((kInputData.size() / block_size + 1) * block_size);
    input_corrected.resize(corrected_size);
    output_bits.reserve(corrected_size*3);
    int num_blocks = corrected_size / block_size;
    
    for (size_t block_it = 0; block_it < num_blocks; ++block_it)
    {
        std::vector<Bit_t> input_block;
        int offset = block_it * block_size;
        input_block.insert(input_block.begin(), input_corrected.begin()+ offset, input_corrected.begin() + offset + block_size);

        std::vector<Bit_t> interleaved_bits;
        m_interleaver.Interleave(input_block, interleaved_bits);

        std::vector<Bit_t> encoded_bits_1;
        std::vector<Bit_t> encoded_bits_2;

        m_coder_1.Encode(input_corrected, encoded_bits_1);
        m_coder_2.Encode(interleaved_bits, encoded_bits_2);

        for(size_t bit_it = 0; bit_it < block_size; ++bit_it)
        {
            output_bits.push_back(encoded_bits_1.at(2*bit_it));
            output_bits.push_back(encoded_bits_1.at(2*bit_it+1));
            output_bits.push_back(encoded_bits_2.at(bit_it));
        }
    }
}
