#include "pch.h"
#include <fstream>
#include "json.hpp"
#include "JsonParser.h"

struct FrameInfo {
	std::string tag;
	int from;
	int to;
};

AnimationClips JsonParser::Load(const std::filesystem::path& jsonPath) // 두형식 둘다 호환됨
{
    std::ifstream ifs(jsonPath);
    if (!ifs) { std::cerr << "Json 파일을 열 수 없습니다.\n"; return {}; }

    nlohmann::json js;  ifs >> js;
    if (js.is_discarded()) { std::cerr << "JSON 파싱 실패\n"; return {}; }

    struct Tag { std::string name; int from; int to; };
    std::vector<Tag> tags;
    for (auto& t : js["meta"]["frameTags"])
        tags.push_back({ t["name"], t["from"], t["to"] });

    std::vector<nlohmann::json> frames;
    if (js["frames"].is_array()) {                    
        frames.assign(js["frames"].begin(), js["frames"].end());
    }
    else {                                   
        for (auto& kv : js["frames"].items())
            frames.push_back(kv.value());          
    }

    AnimationClips clips;
    for (auto& tag : tags)
    {
        AnimationClip clip(tag.name);
        for (int i = tag.from; i <= tag.to; ++i)
        {
            auto& f = frames[i];
            FrameData src;
            src.rect.left = f["frame"]["x"];
            src.rect.top = f["frame"]["y"];
            src.rect.right = src.rect.left + f["frame"]["w"];
            src.rect.bottom = src.rect.top + f["frame"]["h"];
            src.duration = f["duration"].get<float>() / 1000.f;
            clip.AddFrame(src);
        }
        clips.emplace_back(std::move(clip));
    }
    return clips;

	return clips;
}
