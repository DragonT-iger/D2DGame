#pragma once

struct FrameData
{
	D2D1_RECT_U rect;

	int frameIndex; // ������ �ε���
	float duration; // ������ ���� �ð� (�� ����)

	float GetWidth() const { return rect.right - rect.left; }
	float GetHeight() const { return rect.bottom - rect.top; }

	D2D1_RECT_F ToRectF() const
	{
		return D2D1::RectF(
			static_cast<float>(rect.left),
			static_cast<float>(rect.top),
			static_cast<float>(rect.right),
			static_cast<float>(rect.bottom));
	}
};

//��������Ʈ�� �ִϸ��̼� ������ ������ ����, ������Ʈ �ƴ�

class AnimationClip
{
public:
	AnimationClip() = default;
	~AnimationClip() = default;

	void SetBitmap(Microsoft::WRL::ComPtr<ID2D1Bitmap1> sheet) { m_sheet = std::move(sheet); }

	void AddFrame(const FrameData& frame)
	{
		m_frames.emplace_back(frame);
		m_totalDuration += frame.duration;
	}

	void SetLooping(bool looping) { isLoop = looping; }
	bool IsLooping() const { return isLoop; }	

private:
	Microsoft::WRL::ComPtr<ID2D1Bitmap1> m_sheet; // �ִϸ��̼� ��Ʈ ��Ʈ��
	std::vector<FrameData>									m_frames; // ������ ������
	float											m_totalDuration = 0.0f; // ��ü �ִϸ��̼� ���� �ð� (�� ����)
	bool															isLoop = false;	//���� ����
};
