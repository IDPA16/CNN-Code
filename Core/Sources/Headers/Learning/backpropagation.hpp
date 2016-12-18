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
			classification_count = dynamic_cast<Layer::FullyConnectedNeuralNetwork*>(network->layers.end()->get())->outputNeurons.size();

			for (size_t i = 0; i < classification_count; i++)
			{
				output_errors[i] = 0; // initialize with zero
			}
		}

		auto EvaluateSet(typename parent_t::networks_t::iterator network, typename TrainingData<Classification>::const_iterator set) -> void override {
			auto outputs = network->GetOutputsUsingMatrix(set->multiMatrix);		

			for (size_t i = 0; i < classification_count; i++)
			{
				// (zu erreichender - erreichte)^2 durchschnitt von allen trainingssets -> cost function
				output_errors[i] += std:pow(static_cast<Matrix::element_t>(static_cast<set->classification>(i)) - outputs[i]);
			}


			evaluated_network_count++;
		}

		auto EndEpoch(typename parent_t::networks_t::iterator network) -> void override {
			for (auto& layer : network->layers) {
				if (auto* filter = dynamic_cast<Layer::Filter*>(layer.get())) {
					// adjust weights
				}

				if (auto* maxpooler = dynamic_cast<Layer::Pooler::MaxPooler*>(layer.get())) {
					// adjust weights
				}

				if (auto* fully_connected = dynamic_cast<Layer::FullyConnectedNeuralNetwork*>(layer.get())) {
					// adjust weights
				}
			}
		}

		auto GetChamp() const -> typename parent_t::network_t override {
			return parent_t::neuralNetworks.front(); 
		}

		private:
			size_t classification_count;
			std::vector<Matrix::element_t> output_errors;
			size_t evaluated_network_count;
	};
}
