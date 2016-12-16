#pragma once
#include "Learning/learning_method.hpp"

namespace Convolutional::Learning {

	template<typename Classification>
	class Backpropagation : public ILearningMethod<Classification> {
	public:
		using parent_t = ILearningMethod<Classification>;
		using parent_t::ILearningMethod;

		auto IsFinished() const -> bool override { 
			static int runs = 2;
			return !runs--; 
			// TODO mfi: overwrite all of this, 
			// it's only a testing hack until real logic gets written
		}

		// im doing batch learning.

		auto BeginEpoch(typename parent_t::networks_t::iterator network) -> void override {
			// (zu erreichender - erreichte)^2 durchschnitt von allen trainingssets -> cost function


		}

		auto EvaluateSet(typename parent_t::networks_t::iterator network, typename TrainingData<Classification>::const_iterator set) -> void override {
			network->GetOutputsUsingMatrix(set->multiMatrix);
		}

		auto EndEpoch(typename parent_t::networks_t::iterator network) -> void override {
			for (auto& layer : layers) {
				if (auto* filter = dynamic_cast<Layer::Filter*>(&layer)) {
					filter->DoStuff();
				}


			}
		}

		auto GetChamp() const -> typename parent_t::network_t override {
			return parent_t::neuralNetworks.front(); 
		}
	};

}
