//
//  Quest.cpp
//  old28
//
//  Created by reenboog on 15.12.13.
//
//

#include "Quest.h"
#include "rapidjson/document.h"
#include "cocos2d.h"

USING_NS_CC;

void Quest::load(string file) {
    unsigned long questDataSize = 0;
    unsigned char *t = (FileUtils::getInstance()->getFileData(file.c_str(), "r", &questDataSize));
    
    char *questData = new char[questDataSize + 1];
    memcpy(questData, t, questDataSize);
    questData[questDataSize] = NULL;
    
    delete[] t;
    t = NULL;
    
    rapidjson::Document questDoc;
    questDoc.Parse<0>(questData);
    
    if(questDoc.IsArray()) {
        for(int i = 0; i < questDoc.Size(); ++i) {
            const auto &currentEntry = questDoc[i];
            
            if(currentEntry.IsObject()) {
                QuestEntry questEntry;
                
                questEntry.key = currentEntry["key"].GetInt();
                questEntry.question = currentEntry["q"].GetString();
                
                const auto &answers = currentEntry["answers"];
                
                if(answers.IsArray()) {
                    for(int j = 0; j < answers.Size(); ++j) {
                        const auto &currentAnswer = answers[j];
                        
                        if(currentAnswer.IsObject()) {
                            QuestAnswer questAnswer;
                            
                            questAnswer.caption = currentAnswer["caption"].GetString();
                            const auto &answerTransitions = currentAnswer["transitions"];
                            
                            if(answerTransitions.IsObject()) {
                                const auto &transitionVariants = answerTransitions["variants"];
                                
                                if(transitionVariants.IsArray()) {
                                    for(int k = 0; k < transitionVariants.Size(); ++k) {
                                        const auto &currentVariant = transitionVariants[k];
                                        
                                        if(currentVariant.IsObject()) {
                                            QuestAnswerTransition currentQuestTransition;
                                            currentQuestTransition.message = currentVariant["message"].GetString();
                                            currentQuestTransition.key = currentVariant["key"].GetInt();
                                            
                                            const auto &variantApplyStats = currentVariant["applyStats"];
                                            
                                            auto statNameToEnum = [](string statName) {
                                                if(statName == "money") {
                                                    return ST_Money;
                                                } else if(statName == "health") {
                                                    return ST_Health;
                                                } else if(statName == "kindness") {
                                                    return ST_Kindness;
                                                } else if(statName == "socials") {
                                                    return ST_Socials;
                                                } else if(statName == "gen") {
                                                    return ST_Gen;
                                                } else if(statName == "age") {
                                                    return ST_Age;
                                                }
                                                
                                                // something really bad happend
                                                assert(0);
                                            };
                                            
                                            if(variantApplyStats.IsObject()) {
                                                for(auto variantStatIt = variantApplyStats.MemberBegin();
                                                    variantStatIt != variantApplyStats.MemberEnd(); ++variantStatIt) {

                                                    string statName = variantStatIt->name.GetString();
                                                    int statValue = variantStatIt->value.GetInt();
                                                    
                                                    StatType statType = statNameToEnum(statName);
                                                    currentQuestTransition.statsToApply.addStat(statType, statValue);
                                                }
                                            }
                                            
                                            //TransitionOptionPool transitionOptions;
                                            
                                            auto applyOption = [&](CompareType compareType, StatType statType, int value) {
                                                currentQuestTransition.requiredOptions.push_back({value, compareType, statType});
                                            };
                                            
                                            const auto &currentVariantOptions = currentVariant["requiredOptions"];
                                            
                                            if(currentVariantOptions.IsObject()) {
                                                for(auto variantOptionsIt = currentVariantOptions.MemberBegin();
                                                    variantOptionsIt != currentVariantOptions.MemberEnd(); ++variantOptionsIt) {
                                                    
                                                    CompareType compareType;
                                                    string compareTypeStr = variantOptionsIt->name.GetString();
                                                    
                                                    if(compareTypeStr == "lessThan") {
                                                        compareType = CT_LessThan;
                                                    } else if(compareTypeStr == "biggerThan") {
                                                        compareType = CT_BiggerThan;
                                                    } else if(compareTypeStr == "equals") {
                                                        compareType = CT_Equals;
                                                    }
                                                    
                                                    const auto &compareValues = variantOptionsIt->value;
                                                    
                                                    if(compareValues.IsObject()) {
                                                        for(auto currentComparedValueIt = compareValues.MemberBegin();
                                                            currentComparedValueIt != compareValues.MemberEnd(); ++currentComparedValueIt) {
                                                            string statName = currentComparedValueIt->name.GetString();
                                                            
                                                            StatType statType = statNameToEnum(statName);
                                                            int statValue = currentComparedValueIt->value.GetInt();
                                                            
                                                            applyOption(compareType, statType, statValue);
                                                        }
                                                    }
                                                }

                                            }
                                            
                                            questAnswer.transitions.push_back(currentQuestTransition);
                                        }
                                    }
                                    
                                }
                            }
                            
                            questEntry.answers.push_back(questAnswer);
                        }
                    }
                }
                
                entries.push_back(questEntry);
                
            }
        }
        
//        for(int i = 0; i < entries.size(); ++i) {
//            CCLOG("key: %i", entries[i].key);
//            CCLOG("question: %s", entries[i].question.c_str());
//
//            for(int j = 0; j < entries[i].answers.size(); ++j) {
//                CCLOG("\t answer caption: %s", entries[i].answers[j].caption.c_str());
//                
//                for(int k = 0; k < entries[i].answers[j].transitions.size(); ++k) {
//                    CCLOG("\t\t transition message: %s", entries[i].answers[j].transitions[k].message.c_str());
//                }
//            }
//        }
    }
}

const QuestAnswerTransition& Quest::apply(string caption) {
    return QuestAnswerTransition();
}